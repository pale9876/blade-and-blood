extends PopupPanel
class_name ErrorPanel


@onready var err_name: Label = %ErrName
@onready var err_msg: RichTextLabel = %Message


func _init() -> void:
	Global.err_panel = self
	visible = false


func init_err_msg(_name: String, _msg: String) -> void:
	err_name.text = _name
	err_msg.text = _msg
	visible = true



	
