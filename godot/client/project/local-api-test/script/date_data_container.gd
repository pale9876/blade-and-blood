extends DataContainer
class_name DateDataContainer



func get_value() -> String:
	var _month := (get_node(^"%Month") as SpinBox).value
	var _day := (get_node(^"%Day") as SpinBox).value
	var _year := (get_node(^"%Year") as SpinBox).value
	
	const _TEMP: String = "%s-%s-%s"
	
	return _TEMP % [_month, _day, _year]
