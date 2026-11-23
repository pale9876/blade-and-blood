extends PopupPanel
class_name ResultPanel


const RESULT_TEMP: String = "Result => %s"
const CODE_TEMP: String = "Code => %s"


@onready var _result: Label = %Result
@onready var _code: Label = %Code
@onready var _headers: VBoxContainer = %Headers
@onready var _json: RichTextLabel = %Json
@onready var _accept: Button = %Accept


func _init() -> void:
	visible = false


func _ready() -> void:
	_accept.button_up.connect(
		func() -> void:
			visible = false
			pass
	)


func init_result(result: int, code: int, headers: PackedStringArray, data: String) -> void:
	if is_empty():
		_clear()
	
	_result.text = RESULT_TEMP % str(result)
	_code.text = CODE_TEMP % str(code)
	for header: String in headers:
		var _label: Label = Label.new()
		_label.text = header
		_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
		_headers.add_child(_label)
	_json.text = ' Empty ' if data.is_empty() else data
	
	
	Global.stamp_log({
			"result" : result,
			"code" : code,
			"headers" : headers,
			"body" : data
	})
	


func is_empty() -> bool:
	return _result.text.is_empty()\
	and _code.text.is_empty()\
	and _json.text.is_empty()\
	and _headers.get_child_count() > 0


func _clear() -> void:
	_result.text = ""
	_code.text = ""
	
	for header_label: Node in _headers.get_children():
		header_label.queue_free()
	
	_json.text = ""




	
