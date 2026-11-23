extends HTTPRequest
class_name API

signal completed(result: int, code: int, headers: PackedStringArray, body: String)


func _init() -> void:
	request_completed.connect(
		func(result: int, code: int, headers: PackedStringArray, body: PackedByteArray) -> void:
			var _body: String = body.get_string_from_utf8()
			
			print("------------------------------------")
			print(result)
			print(code as HTTPClient.ResponseCode)
			print(headers)
			print(_body)
			print("------------------------------------")
			
			completed.emit(result, code, headers, _body)
	)
