extends Control
class_name APIControl


const REGISTRY_API_URL: String = "http://127.0.0.1:3000"


@onready var host: LineEdit = %Host
@onready var port_edit: LineEdit = %PortEdit
@onready var scope: LineEdit = %Scope

@onready var api: API = %API
@onready var send_btn: Button = %Send

@onready var result_panel: ResultPanel = %ResultPanel
@onready var http_method_container: TabContainer = %HttpMethodContainer


@onready var save_log_btn: Button = %SaveLogBtn


func _ready() -> void:
	api.completed.connect(
		func (result: int, code: int, headers: PackedStringArray, body: String) -> void:
			result_panel.init_result(result, code, headers, body)
			result_panel.visible = true
	)
	
	send_btn.button_up.connect(
		func() -> void:
			var _headers: PackedStringArray = ["Content-Type: application/json"]
			var request_data: String = ""
			
			api.request(
				get_target_address(),
				_headers,
				get_method(),
				request_data,
			)
	)
	
	save_log_btn.button_up.connect(
		func () -> void:
			Global.save_log()
	)


func get_target_address() -> String:
	var _temp: String = "http://%s:%s/%s"
	var _ip: String = host.text if !host.text.is_empty() else "127.0.0.1"
	var _port: String = port_edit.text if !port_edit.text.is_empty() else "3000"
	var _scope: String = scope.text if !scope.text.is_empty() else ""
	
	return _temp % [_ip, _port, _scope]


func get_method() -> HTTPClient.Method:
	return (
		http_method_container.get_child(
			http_method_container.current_tab
		) as MethodTab
	).method

	
