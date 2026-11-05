"""Import UI textures. Pass an optional texture name to import only that texture.
Also called by setup_unreal.py; never rewrites vehicle or level assets.
"""
import pathlib
import sys
import unreal


def build_menu(names=None):
    root = pathlib.Path(unreal.Paths.project_dir()).resolve()
    unreal.EditorAssetLibrary.make_directory('/Game/UI')
    assets = unreal.AssetToolsHelpers.get_asset_tools()
    sources = {name: root / 'Content/UI' / (name + '.png')
               for name in ('MenuBackground', 'CiazPreview', 'SwiftPreview')}
    sources['DrivingHUD'] = root / 'Docs/UI/ExtractedHUD-v2.png'
    for name in names or sources:
        source = sources[name]
        if not source.is_file():
            raise RuntimeError('Missing menu texture: ' + str(source))
        task = unreal.AssetImportTask()
        for prop, value in [('filename', str(source)), ('destination_path', '/Game/UI'),
                            ('destination_name', 'T_' + name), ('automated', True),
                            ('replace_existing', True), ('save', True)]:
            task.set_editor_property(prop, value)
        assets.import_asset_tasks([task])
        texture = unreal.load_asset('/Game/UI/T_' + name)
        if not isinstance(texture, unreal.Texture2D):
            raise RuntimeError('Failed to import menu texture: ' + name)
        texture.set_editor_property('lod_group', unreal.TextureGroup.TEXTUREGROUP_UI)
        texture.set_editor_property('compression_settings', unreal.TextureCompressionSettings.TC_EDITOR_ICON)
        texture.set_editor_property('mip_gen_settings', unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
        texture.set_editor_property('srgb', True)
        texture.set_editor_property('max_texture_size', 2048 if name in ('MenuBackground', 'DrivingHUD') else 1024)
        if not unreal.EditorAssetLibrary.save_loaded_asset(texture, False):
            raise RuntimeError('Could not save menu texture: ' + name)
        unreal.log('[CiazMenu] Saved ' + texture.get_path_name())


if __name__ == '__main__':
    build_menu(sys.argv[1:])
