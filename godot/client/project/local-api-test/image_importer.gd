extends FileDialog
class_name ImageImporter


signal import_success(path: String, _texture: ImageTexture)


func _init() -> void:
	visible = false
	
	Global.image_importer = self
	
	file_selected.connect(
		func(_path: String) -> void:
			var _image := Image.new()
			
			var err := _image.load(_path)
			if err != OK:
				visible = false
				printerr("Image Importer => 이미지를 불러올 수 없습니다. path : ", _path)
				Global.alert_err("이미지를 불러올 수 없습니다.", "path => " + _path)
				await Global.err_panel.popup_hide
				visible = true
				return
			
			var _texture := ImageTexture.create_from_image(_image)
			import_success.emit(_path, _texture)
			
			visible = false
	)
	


	
