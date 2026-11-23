extends PopupPanel
class_name AddDataPopup


const BIRTH_DATE_DATA_CONTAINER: PackedScene = preload("uid://bcb8xre65jej5")
const EMAIL_DATA_CONTAINER: PackedScene = preload("uid://bj5jwhuunj0iu")
const PASSWORD_DATA_CONTAINER: PackedScene = preload("uid://f0pqlc4swg26")
const STRING_DATA_CONTAINER: PackedScene = preload("uid://b02qawo8mikdm")


@onready var push_data: Button = %PushData
@onready var data_type_option: OptionButton = %DataTypeOption
@onready var data_attr: VBoxContainer = %DataAttr


func _ready() -> void:
	push_data.button_up.connect(
		func() -> void:
			var _container: DataContainer
			match data_type_option.text:
				"String":
					_container = STRING_DATA_CONTAINER.instantiate()
				
	)





	
