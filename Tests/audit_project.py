"""Static source/asset audit, not a substitute for Unreal build/cook."""
import json,pathlib,struct,re,ast,wave
root=pathlib.Path(__file__).resolve().parents[1]
for vehicle_folder in ['VehicleData','SwiftData']:
 manifest=json.loads((root/('Content/'+vehicle_folder+'/vehicle.json')).read_text())
 for part in manifest['parts']:
  b=(root/('Content/'+vehicle_folder)/part['file']).read_bytes();magic,nv,ni=struct.unpack_from('<III',b)
  assert magic==0x43505A31 and ni%3==0 and len(b)==12+nv*32+ni*4,part['file']
  ix=struct.unpack_from('<%dI'%ni,b,12+nv*32);assert max(ix)<nv,part['file']
 for material in manifest['materials']:
  if material['texture']:assert (root/('Content/'+vehicle_folder+'/Textures')/material['texture']).is_file(),material
for entry in json.loads((root/'Tools/ObstacleSource/materials.json').read_text()):
 assert (root/'Tools/ObstacleSource'/entry['file']).is_file(),entry['file']
 for material in entry['materials']:
  if material['texture']:assert (root/'Tools/ObstacleSource/Textures'/material['texture']).is_file(),material
for file in (root/'Tools').glob('*.py'):ast.parse(file.read_text(),filename=str(file))
for file in (root/'Content/AudioSource').glob('*.wav'):
 with wave.open(str(file)) as w:assert w.getnframes()>0 and w.getnchannels()>0,file
for file in (root/'Source').rglob('*'):
 if file.suffix not in ['.h','.cpp','.inl']:continue
 s=re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'','',file.read_text(),flags=re.S)
 stack=[]
 for ch in s:
  if ch in '({[':stack.append(ch)
  elif ch in ')}]':assert stack and stack.pop()=={')':'(',']':'[','}':'{'}[ch],file
 assert not stack,file
config=(root/'Config/DefaultGame.ini').read_text()
for directory in ['Materials','Audio','VehicleTextures','Obstacles','SwiftTextures','SwiftMaterials']:assert f'Path="/Game/{directory}"' in config
assert 'Path="VehicleData"' in config and 'Path="SwiftData"' in config
print('PASS: mesh binary sizes/indices, material texture paths, obstacle sources, WAVs, Python syntax, C++ delimiters and cook/stage directories.')
