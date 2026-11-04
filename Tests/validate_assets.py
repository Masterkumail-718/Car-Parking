"""Validate packaged vehicle binaries, textures, pivots, audio and project wiring."""
from pathlib import Path
import struct,json,wave,math
import numpy as np
from PIL import Image
root=Path(__file__).resolve().parents[1]
data=root/'Content/VehicleData'
m=json.loads((data/'vehicle.json').read_text())
assert m['format']==1
total=0;bounds=[];groups=set();wheel={}
for part in m['parts']:
 b=(data/part['file']).read_bytes()
 magic,n,nt=struct.unpack_from('<III',b)
 assert magic==0x43505A31 and nt%3==0
 assert len(b)==12+n*32+nt*4,(part['file'],len(b),n,nt)
 a=np.frombuffer(b,dtype='<f4',offset=12,count=n*8).reshape(n,8)
 idx=np.frombuffer(b,dtype='<u4',offset=12+n*32,count=nt)
 assert idx.max()<n
 assert np.isfinite(a).all()
 assert np.allclose(np.linalg.norm(a[:,3:6],axis=1),1,atol=1e-3)
 assert 0<=part['material']<len(m['materials'])
 pivot=np.array(part['pivot'])
 v=a[:,:3]+pivot;bounds.append(v)
 total+=nt//3
 groups.add(part['group'])
 if 0<=part['group']<4:
  if part['group'] in wheel:assert np.allclose(wheel[part['group']],pivot,atol=.001)
  wheel[part['group']]=pivot
 # Every nondegenerate face should use Unreal clockwise winding relative to normals.
 t=idx.reshape(-1,3)
 cross=np.cross(a[t[:,1],:3]-a[t[:,0],:3],a[t[:,2],:3]-a[t[:,0],:3])
 dots=(cross*a[t[:,0],3:6]).sum(axis=1)
 assert (dots>1e-2).sum()==0,part['file']
assert total==447992
assert groups=={-1,0,1,2,3,4}
v=np.concatenate(bounds)
assert abs(np.ptp(v[:,0])-449)<.1
assert abs(abs(wheel[0][0]-wheel[2][0])-265)<1
for mat in m['materials']:
 if mat['texture']:
  p=data/'Textures'/mat['texture'];assert p.is_file()
  with Image.open(p) as im:
   assert max(im.size)<=1024
   im.verify()
for name in ['EngineIdle','EngineLoad','SensorTone','Impact','Success','Failure']:
 with wave.open(str(root/'Content/AudioSource'/f'{name}.wav')) as w:
  assert w.getnchannels()==1 and w.getsampwidth()==2 and w.getnframes()>0
project=json.loads((root/'CiazParking.uproject').read_text())
assert project['EngineAssociation']=='5.4'
assert 'VehicleData' in (root/'Config/DefaultGame.ini').read_text()
assert 'r.RayTracing=False' in (root/'Config/DefaultEngine.ini').read_text()
print(f'PASS: {len(m["parts"])} mesh batches, {total:,} triangles, 4 shared wheel pivots, steering pivot, texture references, winding, dimensions, audio, staging config.')
