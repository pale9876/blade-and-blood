@tool
extends TextureRect
class_name ImagePreviewRect



func _init() -> void:
	expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
	custom_minimum_size = Vector2(40., 40.)
	custom_maximum_size = Vector2(128., 128.)


	
