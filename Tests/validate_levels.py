"""Conservative 2D footprint checks; not a substitute for driving each course."""
from pathlib import Path
import json,math
ROOT=Path(__file__).resolve().parents[1]
SIZES={'Car1':(487.07,205.71),'Car2':(470,224.76*470/560.06),'Car3':(382.46,168.72),'Barrier':(176.52,64.84),'Bollard':(20,20),'Cone':(41.31,41.31),'Wall':(200,10),'Curb':(200,100),'CurbCorner':(200,200)}
def rect(x,y,yaw,l,w):
 a=math.radians(yaw);c,s=math.cos(a),math.sin(a)
 return [(x+u*c-v*s,y+u*s+v*c) for u,v in [(-l/2,-w/2),(l/2,-w/2),(l/2,w/2),(-l/2,w/2)]]
def overlap(a,b):
 for p in [a,b]:
  for i in range(4):
   dx=p[(i+1)%4][0]-p[i][0];dy=p[(i+1)%4][1]-p[i][1]
   pa=[x*(-dy)+y*dx for x,y in a];pb=[x*(-dy)+y*dx for x,y in b]
   if max(pa)<=min(pb) or max(pb)<=min(pa):return False
 return True
levels=json.loads((ROOT/'Docs/level_layouts.json').read_text())
assert len(levels)==10
for d in levels:
 assert d['width']>190 and d['length']>449
 spawn=rect(*d['spawn'][:2],d['spawn_yaw'],449,190)
 target=rect(*d['target'][:2],d['target_yaw'],d['length'],d['width'])
 for ob in d['obstacles']:
  footprint=rect(*ob['p'][:2],ob['yaw'],*SIZES[ob['asset']])
  assert not overlap(spawn,footprint),(d['name'],'spawn',ob)
  assert not overlap(target,footprint),(d['name'],'bay',ob)
 print('PASS:',d['name'],'spawn and whole target clear;',len(d['obstacles']),'obstacles')
if __name__=='__main__':
 import matplotlib
 matplotlib.use('Agg')
 import matplotlib.pyplot as plt
 from matplotlib.patches import Polygon
 fig,axes=plt.subplots(5,2,figsize=(16,25),facecolor='#101820')
 colours={'Car1':'#3a86b6','Car2':'#66a2b3','Car3':'#356c7d','Barrier':'#9a9b95','Cone':'#f39739','Bollard':'#e9bc54','Wall':'#59616a','Curb':'#8e8579','CurbCorner':'#8e8579'}
 for ax,d in zip(axes.flat,levels):
  ax.set_facecolor('#222c35')
  for ob in d['obstacles']:
   ax.add_patch(Polygon(rect(*ob['p'][:2],ob['yaw'],*SIZES[ob['asset']]),facecolor=colours[ob['asset']],edgecolor='#121820',lw=.3))
  ax.add_patch(Polygon(rect(*d['target'][:2],d['target_yaw'],d['length'],d['width']),fill=False,edgecolor='#f5c44e',lw=2))
  ax.add_patch(Polygon(rect(*d['spawn'][:2],d['spawn_yaw'],449,190),facecolor='#91dfb4',edgecolor='white'))
  for xy,angle,colour in [(d['spawn'],d['spawn_yaw'],'white'),(d['target'],d['target_yaw'],'#f5c44e')]:
   a=math.radians(angle);ax.arrow(xy[0],xy[1],150*math.cos(a),150*math.sin(a),width=12,head_width=60,color=colour)
  ax.set_xlim(-3050,3050);ax.set_ylim(-2250,2250);ax.set_aspect('equal');ax.set_title(d['name'],color='white',fontsize=14);ax.set_xticks([]);ax.set_yticks([])
 fig.suptitle('CIAZ PARKING / BETA 1.4 COURSE PLANS\nGreen: spawn   Gold: target   Blue: parked cars   Grey: barriers, walls and curbs',color='white',fontsize=18,y=.99)
 fig.tight_layout(rect=[0,0,1,.96]);fig.savefig(ROOT/'Docs/Level_Plans.png',dpi=120);plt.close(fig)
