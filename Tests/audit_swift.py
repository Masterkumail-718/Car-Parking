"""Asset validation; requires numpy/scipy. Does not replace an Unreal build."""
from pathlib import Path
import json,struct,numpy as np
from scipy.spatial import ConvexHull
r=Path(__file__).resolve().parents[1];d=r/'Content/SwiftData';m=json.loads((d/'vehicle.json').read_text());hulls=json.loads((d/'collision.json').read_text())['hulls']
assert m['triangles']==m['source_triangles']
triangle_count=0
for p in m['parts']:
 b=(d/p['file']).read_bytes();magic,nv,ni=struct.unpack_from('<III',b);assert magic==0x43505A31 and len(b)==12+nv*32+ni*4 and ni%3==0
 a=np.frombuffer(b,'<f4',nv*8,12).reshape(-1,8);t=np.frombuffer(b,'<u4',ni,12+nv*32);assert np.isfinite(a).all() and t.max()<nv
 triangle_count+=ni//3
 if p['group'] in [5,6]:assert abs(np.linalg.norm(p['axis'])-1)<1e-5 and p['zero_angle']==0 and p['sweep']==-270
for gr in range(10):assert any(p['group']==gr for p in m['parts'])
assert all(p['name']=='Needle.001' for p in m['parts'] if p['group']==5)
assert all(p['name']=='Needle' for p in m['parts'] if p['group']==6)
for gr in range(4):
 pivots=[p['pivot'] for p in m['parts'] if p['group']==gr];assert np.max(np.ptp(pivots,axis=0))<1e-5
 assert np.allclose(pivots[0],m['wheel_pivots'][gr],rtol=0,atol=1e-5)
assert triangle_count==m['source_triangles']
assert np.allclose(np.array(m['wheel_pivots'])[:,2]-m['wheel_radius'],-m['origin_height'],rtol=0,atol=.01)
for mat in m['materials']:
 for role in ['texture','normal','packed']:
  if mat.get(role):assert (d/'Textures'/mat[role]).is_file()
planes=[ConvexHull(np.array(h)).equations for h in hulls]
def inside(pt):return any(np.all(eq[:,:3]@pt+eq[:,3]<=1e-5) for eq in planes)
assert inside(np.array([0,0,-40.])), 'central chassis must collide'
for p in m['wheel_pivots']:
 assert not inside(np.array(p)), 'wheel centre must be outside chassis collision'
 assert not inside(np.array(p)+[0,0,15]), 'wheel arch must have upward travel'
assert max(len(h) for h in hulls)<=48
assert len(hulls)<=50
print('PASS Swift source triangle count, mesh buffers, animation groups, textures, wheel placement and chassis collision.')
