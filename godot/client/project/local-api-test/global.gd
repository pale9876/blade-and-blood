extends Node


var err_panel: ErrorPanel
var image_importer: ImageImporter
var log: Dictionary = {}


func alert_err(err_name: String, err_msg: String) -> void:
	err_panel.init_err_msg(err_name, err_msg)


func stamp_log(data: Dictionary) -> void:
	var time_stamp: String = Time.get_time_string_from_system()
	log[time_stamp] = data


func save_log() -> void:
	var file := FileAccess.open("", FileAccess.WRITE)
	file.store_string(JSON.stringify(log))
	
	
	pass


func update_log() -> void:
	pass

	
