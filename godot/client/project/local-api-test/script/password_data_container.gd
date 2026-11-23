extends DataContainer
class_name PasswordContainer


@onready var sha_256: CheckBox = $Sha256


func get_value() -> String:
	var _password: String = (get_node(^"Value") as LineEdit).text
	return _password.sha256_text() if sha_256.button_pressed else _password
