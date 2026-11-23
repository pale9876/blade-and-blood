@tool
extends LineEdit
class_name PasswordEdit


func _init() -> void:
	secret = true
	virtual_keyboard_enabled = true
	virtual_keyboard_type = LineEdit.KEYBOARD_TYPE_PASSWORD
	
