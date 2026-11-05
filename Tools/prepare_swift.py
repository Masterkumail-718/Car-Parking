import sys,struct,zlib,json,zipfile,re
from pathlib import Path
import numpy as np
from PIL import Image
import io
OUT=Path(sys.argv[2])
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
# Swift-specific conversion. numpy/Pillow/scipy required.
from scipy.spatial import ConvexHull
import hashlib
source=Path(sys.argv[1]).parent/'textures'
A=np.array([[0,0,1],[-1,0,0],[0,1,0]],float)
# Source is correctly centimetre scaled: 384.23 cm long, 244.95 cm wheelbase.
shift=np.array([166.43,0,-59.64])
def transformed(g,mid):return (val(g,'Vertices').reshape(-1,3)@world(mid)[:3,:3].T+world(mid)[:3,3])@A.T+shift
materials=[];matids={};seen={}
def texture_file(base,normal=False):
 p=source/base
 if not p.exists():return ''
 with Image.open(p) as source_image:
  im=source_image.convert('RGBA' if source_image.mode=='RGBA' or 'transparency' in source_image.info else 'RGB')
 if normal:
  a=np.array(im);a[:,:,1]=255-a[:,:,1];im=Image.fromarray(a) # supplied OpenGL normal -> DirectX
 data=io.BytesIO();im.save(data,format='PNG');key=hashlib.sha256(data.getvalue()).hexdigest()
 if key not in seen:
  seen[key]=('N_' if normal else '')+base;(OUT/'Textures'/seen[key]).write_bytes(data.getvalue())
 return seen[key]
for o in objs:
 if o['n']!='Material':continue
 mid=o['p'][0];matids[mid]=len(materials);p=props(o);nm=name(o);low=nm.lower()
 tex='';normal=''
 for c in cons:
  if c[0]=='OP' and c[2]==mid:
   t=byid[c[1]];raw=val(t,'FileName',val(t,'RelativeFilename',''));base=raw.replace('\\','/').split('/')[-1]
   if 'Diffuse' in c[3]:tex=texture_file(base)
   if 'Normal' in c[3]:normal=texture_file(base,True)
 # Some supplied albedo textures have no FBX connection.
 if not tex:tex=texture_file(nm.split('.')[0]+'_baseColor.png')
 chrome='chrome' in low or low in ['rim_breaks','seat_metal','roof_metal','roof_metal.001']
 paint='carpaint' in low or 'carpaint' in low.replace('_','')
 glass=low in ['windows','light_glass']
 rubber='tire' in low or 'rubber' in low
 fabric=any(x in low for x in ['cloth','fab','carpet','seatb'])
 rough=.22 if chrome else (.28 if paint else (.1 if glass else (.88 if rubber or fabric else .67)))
 col=p.get('DiffuseColor',[.1,.1,.1])[:3]
 if rubber:col=[.025,.025,.028]
 if glass:col=[.15,.19,.22]
 if low=='red_glass':col=[.35,.008,.006];rough=.22
 if low=='orange_glass':col=[.65,.17,.008];rough=.24
 # Packed maps are glTF metallic/roughness, never base colour. Their red
 # channel is zero (not AO); use green for roughness, blue for metallic.
 packed=texture_file(nm.split('.')[0]+'_metallicRoughness.png')
 materials.append(dict(name=nm,texture=tex,normal=normal,packed=packed,color=col,glass=glass,paint=paint,interior=not glass and not paint,metallic=1 if chrome else (.15 if paint else 0),roughness=rough,specular=.35 if rubber or fabric else .5,opacity=.16 if low=='windows' else (.24 if glass else 1)))
# Wheel centres from tread geometry, not from rim hardware.
tirepair=next((g,mid) for mid in models for g in [byid[c[1]] for c in cons if c[0]=='OO' and c[2]==mid and c[1] in byid and byid[c[1]]['n']=='Geometry'] if 'TYRE_MESH_Tire_Tred' in name(models[mid]))
tv=transformed(*tirepair)
# Keep the FBX wheel proportions and place the tread at the runtime ground plane.
ground_shift=-80-tv[:,2].min()
shift[2]+=ground_shift
tv[:,2]+=ground_shift
wp=[]
for group in range(4):
 vv=tv[(tv[:,0]>0)==(group<2)];vv=vv[(vv[:,1]>0)==(group%2==1)];wp.append((vv.min(0)+vv.max(0))/2)
wp=np.array(wp);radius=(tv[:,2].max()-tv[:,2].min())/2
parts=[];batches={};source_triangles=0;bodypoints=[];gauge_info={}
for c in cons:
 if c[0]!='OO' or c[1] not in byid or byid[c[1]]['n']!='Geometry' or c[2] not in models:continue
 g=byid[c[1]];mid=c[2];nm=name(models[mid]);w=world(mid);v=transformed(g,mid)
 raw=val(g,'PolygonVertexIndex').astype(np.int64);ix=np.where(raw<0,-raw-1,raw)
 # Fan triangulate any source quads. Keep original per-corner UV/normal indices.
 ends=np.flatnonzero(raw<0);tri=[];faceids=[];start=0
 for face,end in enumerate(ends):
  for j in range(start+1,end):tri.append([start,j,j+1]);faceids.append(face)
  start=end+1
 tri=np.array(tri);source_triangles+=len(tri)
 norms=layer(g,'LayerElementNormal','Normals','NormalsIndex',3,ix)@np.linalg.inv(w[:3,:3])@A.T
 norms/=np.maximum(np.linalg.norm(norms,axis=1,keepdims=True),1e-10)
 uv=layer(g,'LayerElementUV','UV','UVIndex',2,ix);uv[:,1]=1-uv[:,1]
 ml=ch(g,'LayerElementMaterial');mi=val(ml,'Materials');mi=np.full(len(tri),mi[0]) if val(ml,'MappingInformationType')=='AllSame' else mi[np.array(faceids)]
 attached=[cc[1] for cc in cons if cc[0]=='OO' and cc[2]==mid and cc[1] in matids]
 group=np.full(len(tri),-1);cent=v[ix[tri]].mean(1)
 if '_WHEEL_' in nm:group=(cent[:,0]<0).astype(int)*2+(cent[:,1]>0).astype(int)
 elif nm=='Steering Wheel':group[:]=4
 elif nm in ['Needle','Needle.001']:group[:]=6 if nm=='Needle' else 5
 elif nm=='Mirror':group[:]=7+(cent[:,1]>0).astype(int)
 elif nm=='Rear view Mirror':group[:]=9
 if 'CARBODY' in nm:bodypoints.append(v)
 for gr in np.unique(group):
  pivot=np.zeros(3);axis=None
  if 0<=gr<4:pivot=wp[gr]
  elif gr>=4:
   vv=v[ix[tri[group==gr]].ravel()];pivot=(vv.min(0)+vv.max(0))/2
   if gr==4:
    # Fit rim plane, excluding stalks/hub (separate supplied object).
    axis=np.linalg.eigh(np.cov(vv.T))[1][:,0];axis*=1 if axis[0]>0 else -1
    # Fit the circular upper rim in its own plane; do not pivot around the
    # asymmetric D-shaped bounding box or the offset spoke mass.
    basis=np.linalg.eigh(np.cov(vv.T))[1][:,1:];origin=vv.mean(0);q=(vv-origin)@basis
    rr=np.linalg.norm(q,axis=1);keep=(rr>15)&(vv[:,2]>np.median(vv[:,2])-8)
    qk=q[keep];fit=np.linalg.lstsq(np.column_stack([2*qk[:,0],2*qk[:,1],np.ones(len(qk))]),(qk*qk).sum(1),rcond=None)[0]
    pivot=origin+basis@fit[:2]
   if gr in [5,6]:
    # Dense circular needle hub is at upper end of the supplied vertical pointer.
    pivot=(vv[vv[:,1].argmin()]+vv[vv[:,1].argmax()])*.5
    axis=np.linalg.eigh(np.cov(vv.T))[1][:,0];axis*=1 if axis[0]>0 else -1
    gauge_info[int(gr)]=dict(pivot=pivot.tolist(),axis=axis.tolist())
  for slot in np.unique(mi[group==gr]):
   t=tri[(group==gr)&(mi==slot)];pp=v[ix].copy()
   pp=pp-pivot;attrs=np.concatenate([pp,norms,uv],axis=1).astype('<f4')
   used,remap=np.unique(t,return_inverse=True);attrs=attrs[used];t=remap.reshape(-1,3)
   # Weld only identical position/normal/UV vertices, keeping seams.
   _,idx,inv=np.unique(attrs,axis=0,return_index=True,return_inverse=True);attrs=attrs[idx];t=inv[t]
   if gr in [7,8,9]:
    # Give each mirror its own full render-target UV rectangle.
    mn=attrs[:,[1,2]].min(0);span=np.maximum(.01,np.ptp(attrs[:,[1,2]],axis=0));attrs[:,6:]=1-(attrs[:,[1,2]]-mn)/span

   mat=matids[attached[slot]] if slot<len(attached) else 0
   cross=np.cross(attrs[t[:,1],:3]-attrs[t[:,0],:3],attrs[t[:,2],:3]-attrs[t[:,0],:3]);wrong=(cross*attrs[t[:,0],3:6]).sum(1)>0;t[wrong]=t[wrong][:,[0,2,1]]
   key=(int(gr),mat);batch=batches.setdefault(key,dict(attrs=[],tri=[],pivot=pivot,axis=axis,names=[]));off=sum(len(a) for a in batch['attrs']);batch['attrs'].append(attrs);batch['tri'].append(t+off);batch['names'].append(nm)
for (gr,mat),b in batches.items():
 aa=np.concatenate(b['attrs']).astype('<f4');tt=np.concatenate(b['tri']).astype('<u4').ravel();filename='mesh_%03d.bin'%len(parts)
 (OUT/filename).write_bytes(struct.pack('<III',0x43505A31,len(aa),len(tt))+aa.tobytes()+tt.tobytes())
 part=dict(name=b['names'][0],source_parts=b['names'],file=filename,material=mat,group=gr,pivot=b['pivot'].tolist())
 if b['axis'] is not None:part['axis']=b['axis'].tolist()
 if gr in [5,6]:part['zero_angle']=0.;part['sweep']=-270.
 parts.append(part)
# Separate compound collision: central underbody plus side slices above arches.
points=np.concatenate(bodypoints);hulls=[]
for ylo,yhi in [(-57,57),(-87,-56),(56,87)]:
 for xlo,xhi in zip(np.arange(-192,192,24),np.arange(-168,216,24)):
  vv=points[(points[:,0]>=xlo-2)&(points[:,0]<=xhi+2)&(points[:,1]>=ylo-1)&(points[:,1]<=yhi+1)].copy()
  if len(vv)<8:continue
  floor=-64.1+ground_shift
  if ylo!=-57:
   for p in wp[::2]:
    dist=max(xlo-p[0],p[0]-xhi,0)
    if dist<37:floor=max(floor,p[2]+np.sqrt(37**2-dist**2)+2)
  vv=vv[vv[:,2]>=floor]
  if len(vv)<8:continue
  try:
   h=ConvexHull(vv);verts=vv[h.vertices]
   # Bound hull complexity by an outer directional support-point selection.
   if len(verts)>48:
    dirs=np.array([[x,y,z] for x in [-1,0,1] for y in [-1,0,1] for z in [-1,0,1] if x or y or z]);verts=verts[np.unique((verts@dirs.T).argmax(0))]
   hulls.append(verts.tolist())
  except Exception:pass
(OUT/'collision.json').write_text(json.dumps({'hulls':hulls,'clearance_cm':80+min(p[2] for hull in hulls for p in hull),'wheel_arch_radius_cm':37},indent=2),newline='\n')
manifest=dict(format=1,car='Suzuki Swift 2022',units='cm',origin_height=80,length=384,width_with_mirrors=185,materials=materials,parts=parts,wheel_radius=radius,wheel_pivots=wp.tolist(),source_triangles=source_triangles,triangles=sum(len(b['tri'][i]) for b in batches.values() for i in range(len(b['tri']))),vertices=sum(sum(len(a) for a in b['attrs']) for b in batches.values()),collision_hulls=len(hulls))
(OUT/'vehicle.json').write_text(json.dumps(manifest,indent=2),newline='\n');print({k:v for k,v in manifest.items() if k not in ['materials','parts']});print('Gauges',gauge_info)
