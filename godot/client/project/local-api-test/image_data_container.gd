extends DataContainer


signal image_dropped(path: String)


@onready var preview: ImagePreviewRect = %preview
@onready var file_path: Button = %FilePath


func _enter_tree() -> void:
	var window := get_window()
	
	window.files_dropped.connect(
		func (_files: PackedStringArray) -> void:
			if !has_mouse_point():
				return
			
			for file: String in _files:
				var image := Image.new()
				if image.load(file) == OK:
					var _texture := ImageTexture.create_from_image(image)
					preview.texture = _texture
	)


func _ready() -> void:
	file_path.button_up.connect(
		func() -> void:
			Global.image_importer.popup_file_dialog()
	)
	
	
	Global.image_importer.import_success.connect(
		func (_path: String, _texture: ImageTexture) -> void:
			file_path.text = _path
			preview.texture = _texture
	)



func _gui_input(event: InputEvent) -> void:
	if event is InputEventMouseMotion:
		pass
	
	if event is InputEventMouseButton:
		pass


func has_mouse_point() -> bool:
	return get_rect().has_point(get_global_mouse_position())


func get_value() -> String:
	var is_texture: bool = preview.texture != null
	var buffer_str: String = ""
	if is_texture:
		buffer_str = preview.texture.get_image().get_data().get_string_from_utf8()
	return buffer_str
