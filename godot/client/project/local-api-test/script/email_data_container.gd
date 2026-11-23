extends DataContainer
class_name EmailDataContainer


const _EMAIL_TEMP: String = "%s@%s"


@onready var user_id: LineEdit = $UserId
@onready var domain: LineEdit = $Domain


func get_value() -> String:
	return _EMAIL_TEMP % [user_id.text, domain.text]
