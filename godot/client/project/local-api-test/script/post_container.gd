extends Control



@onready var data_attr: VBoxContainer = %DataAttr


@onready var add_data: Button = %AddData
@onready var remove: Button = %Remove


func _ready() -> void:
	add_data.button_up.connect(
		func() -> void:
			pass
	)
	
	remove.button_up.connect(
		func() -> void:
			pass
	)
