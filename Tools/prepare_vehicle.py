# LEGACY SOURCE CONVERTER: not used by SetupProject. Regenerating vehicle data
# with this script discards the later gauge/mirror splits. Work on a copy only.
"""Offline asset conversion used for this prototype. Requires numpy and Pillow.
Reads the supplied binary FBX, bakes hierarchy transforms, welds identical
position/normal/UV tuples, and writes runtime mesh data (centimetres, X forward).
Run: python prepare_vehicle.py path/to/car.fbx path/to/textures.zip
"""
import sys,struct,zlib,json,zipfile,re
from pathlib import Path
import numpy as np
from PIL import Image
import io
OUT=Path(__file__).resolve().parents[1]/'Content/VehicleData'
OUT.mkdir(parents=True,exist_ok=True);(OUT/'Textures').mkdir(exist_ok=True)
f=open(sys.argv[1],'rb');f.seek(23);version=struct.unpack('<I',f.read(4))[0]
assert version==7400,'Converter supports FBX 7400'
def prop():
 t=f.read(1).decode()
 fmt={'Y':'h','C':'?','I':'i','F':'f','D':'d','L':'q'}
 if t in fmt:return struct.unpack('<'+fmt[t],f.read(struct.calcsize(fmt[t])))[0]
 if t in 'fdlibc':
  n,e,s=struct.unpack('<III',f.read(12));b=f.read(s)
  if e:b=zlib.decompress(b)
  return np.frombuffer(b,dtype={'f':'<f4','d':'<f8','l':'<i8','i':'<i4','b':'i1','c':'i1'}[t]).copy()
 n=struct.unpack('<I',f.read(4))[0];b=f.read(n)
 return b.decode(errors='replace') if t=='S' else b
def node():
 end,n,s=struct.unpack('<III',f.read(12));l=f.read(1)[0]
 if not end:return None
 k=f.read(l).decode();ps=[prop() for _ in range(n)];ch=[]
 while f.tell()<end:
  q=node()
  if q is None:break
  ch.append(q)
 f.seek(end);return {'n':k,'p':ps,'c':ch}
roots=[]
while True:
 q=node()
 if q is None:break
 roots.append(q)
def ch(n,k):return next((q for q in n['c'] if q['n']==k),None)
def val(n,k,default=None):
 q=ch(n,k);return q['p'][0] if q and q['p'] else default
def props(n):
 q=ch(n,'Properties70');return {x['p'][0]:x['p'][4:] for x in q['c']} if q else {}
objs=next(x for x in roots if x['n']=='Objects')['c']
cons=[x['p'] for x in next(x for x in roots if x['n']=='Connections')['c']]
byid={x['p'][0]:x for x in objs}
models={i:x for i,x in byid.items() if x['n']=='Model'}
parents={c[1]:c[2] for c in cons if c[0]=='OO' and c[1] in models}
def name(o):return o['p'][1].split('\x00')[0]
def local(m):
 p=props(m);x,y,z=np.radians(p.get('Lcl Rotation',[0,0,0]))
 rx=np.array([[1,0,0],[0,np.cos(x),-np.sin(x)],[0,np.sin(x),np.cos(x)]])
 ry=np.array([[np.cos(y),0,np.sin(y)],[0,1,0],[-np.sin(y),0,np.cos(y)]])
 rz=np.array([[np.cos(z),-np.sin(z),0],[np.sin(z),np.cos(z),0],[0,0,1]])
 t=np.eye(4);t[:3,:3]=rz@ry@rx@np.diag(p.get('Lcl Scaling',[1,1,1]));t[:3,3]=p.get('Lcl Translation',[0,0,0]);return t
cache={}
def world(i):
 if i not in cache:cache[i]=(world(parents[i]) if parents.get(i) in models else np.eye(4))@local(models[i])
 return cache[i]
def layer(g,key,data,indices,dim,vertex_ids):
 l=ch(g,key);a=np.asarray(val(l,data)).reshape(-1,dim)
 mapping=val(l,'MappingInformationType');ref=val(l,'ReferenceInformationType')
 ids=vertex_ids if mapping in ['ByVertice','ByVertex','ByControlPoint'] else np.arange(len(vertex_ids))
 if mapping=='AllSame':ids=np.zeros(len(vertex_ids),dtype=int)
 if ref=='IndexToDirect':ids=val(l,indices)[ids]
 return a[ids]
zipf=zipfile.ZipFile(sys.argv[2]);textures={Path(n).name:n for n in zipf.namelist() if not n.endswith('/')}
materials=[];matids={}
for o in objs:
 if o['n']!='Material':continue
 mid=o['p'][0];matids[mid]=len(materials);p=props(o)
 diffuse=p.get('DiffuseColor',[.65,.65,.65])[:3]
 tex=''
 for c in cons:
  if c[0]=='OP' and c[2]==mid and 'Diffuse' in str(c[3]):
   t=byid[c[1]];raw=val(t,'FileName',val(t,'RelativeFilename',''));base=raw.replace('\\','/').split('/')[-1]
   if base in textures:tex=base;break
 mn=name(o);low=mn.lower()
 materials.append({'name':mn,'texture':tex,'color':diffuse,
  'glass':'glass' in low,'metallic':.85 if 'chrome' in low else (.25 if 'primary' in low else 0),
  'roughness':.2 if 'glass' in low else (.23 if 'chrome' in low or 'primary' in low else .7)})
for base,n in textures.items():
 if base.lower().endswith(('.png','.jpeg','.jpg')):
  im=Image.open(zipf.open(n));im.thumbnail((1024,1024))
  buffer=io.BytesIO()
  im.save(buffer,format='JPEG' if base.lower().endswith(('.jpg','.jpeg')) else 'PNG')
  (OUT/'Textures'/base).write_bytes(buffer.getvalue())
# Reference dimension 449 cm; the supplied mesh length is ~512.19 cm.
scale=449/512.18963091
A=np.array([[0,0,-1],[1,0,0],[0,1,0]],dtype=float)
parts=[];counts=[0,0]
for c in cons:
 if c[0]!='OO' or c[1] not in byid or byid[c[1]]['n']!='Geometry' or c[2] not in models:continue
 g=byid[c[1]];m=models[c[2]];nm=name(m);w=world(c[2])
 pos=val(g,'Vertices').reshape(-1,3)
 ix=val(g,'PolygonVertexIndex').astype(np.int64)
 assert len(ix)%3==0 and np.all(ix[2::3]<0),'Only triangle meshes expected'
 ix=np.where(ix<0,-ix-1,ix)
 v=(pos@w[:3,:3].T+w[:3,3])@A.T*scale
 v[:,2]-=.49056888*scale
 v[:,2]-=82
 normals=layer(g,'LayerElementNormal','Normals','NormalsIndex',3,ix)
 normals=normals@np.linalg.inv(w[:3,:3])@A.T
 normals/=np.maximum(np.linalg.norm(normals,axis=1,keepdims=True),1e-10)
 uv=layer(g,'LayerElementUV','UV','UVIndex',2,ix);uv[:,1]=1-uv[:,1]
 pivot=np.zeros(3);group=-1
 if nm.startswith('wheel'):
  center=(v.min(0)+v.max(0))/2
  group=(0 if center[0]>0 else 2)+(1 if center[1]>0 else 0)
  # All five components of each wheel share the tire centre.
  tireid=next(cc[1] for cc in cons if cc[0]=='OO' and cc[2] in models and byid[cc[1]]['n']=='Geometry' and name(models[cc[2]]).startswith(nm.split('_')[0]+'_wheel.009'))
  tire=byid[tireid];tmid=next(cc[2] for cc in cons if cc[1]==tireid and cc[0]=='OO')
  tw=world(tmid);tv=(val(tire,'Vertices').reshape(-1,3)@tw[:3,:3].T+tw[:3,3])@A.T*scale
  pivot=(tv.min(0)+tv.max(0))/2;pivot[2]-=.49056888*scale+82
 elif nm.startswith('steer4_003'):
  group=4;pivot=(v.min(0)+v.max(0))/2
 v=v[ix]-pivot
 # Unreal uses clockwise front faces. Keep transformed imported normals;
 # choose winding opposite the mathematical cross product for front faces.
 tris=np.arange(len(ix)).reshape(-1,3)
 cross=np.cross(v[tris[:,1]]-v[tris[:,0]],v[tris[:,2]]-v[tris[:,0]])
 wrong=(cross*normals[tris[:,0]]).sum(1)>0
 tris[wrong]=tris[wrong][:,[0,2,1]]
 attrs=np.concatenate([v,normals,uv],axis=1).astype('<f4')
 # Exact rounded key preserves seams and hard normals.
 _,unique,inverse=np.unique(np.round(attrs,5),axis=0,return_index=True,return_inverse=True)
 attrs=attrs[unique];tri=inverse[tris].astype('<u4')
 ml=ch(g,'LayerElementMaterial');mi=val(ml,'Materials')
 if val(ml,'MappingInformationType')=='AllSame':mi=np.full(len(tris),mi[0],dtype=int)
 attached=[cc[1] for cc in cons if cc[0]=='OO' and cc[2]==c[2] and cc[1] in matids]
 for slot in sorted(set(mi.tolist())):
  selected=tri[mi==slot];used,remap=np.unique(selected,return_inverse=True)
  aa=attrs[used];tt=remap.astype('<u4').reshape(-1)
  filename='part_%03d.bin'%len(parts)
  with open(OUT/filename,'wb') as out:
   out.write(struct.pack('<III',0x43505A31,len(aa),len(tt)))
   out.write(aa.tobytes());out.write(tt.tobytes())
  parts.append({'name':nm,'file':filename,'material':matids[attached[slot]] if slot<len(attached) else 0,'group':group,'pivot':pivot.tolist()})
  counts[0]+=len(aa);counts[1]+=len(tt)//3
manifest={'format':1,'car':'Suzuki Ciaz 2017','units':'cm','origin_height':82,
 'length':449,'width_with_mirrors':216.28398848*scale,
 'scale_from_source':scale,'materials':materials,'parts':parts,'vertices':counts[0],'triangles':counts[1],
 'wheel_radius':30.65}
(OUT/'vehicle.json').write_text(json.dumps(manifest,indent=2))
print('Exported',len(parts),'sections;',counts,'vertices/triangles;',len(materials),'materials.')
# Batch static body pieces sharing a material. Keep each rotating wheel and
# steering assembly separate. This reduces draw calls without decimating detail.
batches={}
for part in parts:
 key=(part['group'],part['material'])
 batches.setdefault(key,[]).append(part)
merged=[]
for (group,mat),batch in batches.items():
 attrs=[];indices=[];offset=0
 for part in batch:
  b=(OUT/part['file']).read_bytes();_,nv,ni=struct.unpack_from('<III',b)
  aa=np.frombuffer(b,dtype='<f4',offset=12,count=nv*8).reshape(nv,8).copy()
  tt=np.frombuffer(b,dtype='<u4',offset=12+nv*32,count=ni).copy()+offset
  attrs.append(aa);indices.append(tt);offset+=nv
 aa=np.concatenate(attrs);tt=np.concatenate(indices)
 filename='mesh_%03d.bin'%len(merged)
 with open(OUT/filename,'wb') as out:
  out.write(struct.pack('<III',0x43505A31,len(aa),len(tt)));out.write(aa.tobytes());out.write(tt.tobytes())
 merged.append({'name':batch[0]['name'],'file':filename,'material':mat,'group':group,'pivot':batch[0]['pivot'],
 'source_parts':[x['name'] for x in batch]})
for part in parts:(OUT/part['file']).unlink()
manifest['parts']=merged
(OUT/'vehicle.json').write_text(json.dumps(manifest,indent=2))
print('Batched to',len(merged),'draw sections.')
