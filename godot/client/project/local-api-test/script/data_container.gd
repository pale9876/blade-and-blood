extends HBoxContainer
class_name DataContainer


# OVERRIDE
func get_value() -> String:
	return (get_node(^"Value") as LineEdit).text
