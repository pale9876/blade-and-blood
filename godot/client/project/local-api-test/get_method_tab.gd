extends MethodTab
class_name GetMethodTab


@onready var add_data: Button = %AddData
@onready var push_data_panel: PushDataPanel = $PushDataPanel
@onready var requests: VBoxContainer = %Requests


const ALREADY_HAS_NAME_MSG: String = "요청할 데이터 이름을 이미 가지고 있습니다."


func _ready() -> void:
	add_data.button_up.connect(
		func() -> void:
			push_data_panel.visible = true
			push_data_panel.data_name_edit.grab_focus()
			push_data_panel.data_name_edit.edit()
	)
	
	push_data_panel.push.connect(
		func(_text: String) -> void:
			push_data_panel.visible = false

			if has_request(_text):
				Global.alert_err(name, ALREADY_HAS_NAME_MSG)
				push_data_panel.clear()
				return
			
			var _label := Label.new()
			_label.name = StringName(_text)
			_label.text = _text
			_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
			requests.add_child(_label)
			
			push_data_panel.clear()
	)


func has_request(_text: String) -> bool:
	return requests.get_children().filter(
		func(node: Node) -> bool:
			return node.name == StringName(_text)
	).size() > 0


func get_send_data_string() -> String:
	var _arr := PackedStringArray()
	var _cache: Dictionary = {"request" : _arr}
	for request: Node in requests.get_children():
		_arr.push_back((request as Label).text)

	return JSON.stringify(_cache)


	
