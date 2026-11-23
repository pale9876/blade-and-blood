extends PopupPanel
class_name PushDataPanel


signal push(text: String)


@onready var data_name_edit: LineEdit = %DataNameEdit
@onready var push_btn: Button = %PushBtn



func _init() -> void:
	visible = false


func _ready() -> void:
	data_name_edit.text_submitted.connect(
		func (_text: String) -> void:
			push.emit(_text)
	)
	
	push_btn.button_up.connect(
		func() -> void:
			var _dataname = data_name_edit.text
			if !_dataname.is_empty():
				push.emit(_dataname)
	)
	
	

func clear() -> void:
	data_name_edit.text = ""


	
