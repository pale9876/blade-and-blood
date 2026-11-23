using Godot;
using Godot.Collections;


public partial class TaskReservationUI : TabBar
{

	[Signal] public delegate void reservedEventHandler(Dictionary data);


    public override void _Ready()
    {
        base._Ready();

		//
		GetNode<CheckBox>("%CheckWantAlertDay").Toggled += (toggle) =>
		{
			GetNode<HBoxContainer>("%DayCheckBoxContainer").Visible = toggle;
		};

		//
		GetNode<Button>("%Reservation").ButtonUp += () =>
		{
			var task_name = get_task_name();

			if (task_name.Length == 0)
			{
				GD.PrintErr("작업 이름을 입력하세요.");
				return;
			}

			EmitSignalreserved(
				new Dictionary
				{
					{"task_name", task_name},
					{"time", get_task_alert_time()},
					{"is_daily_alert", is_checked_daily_alert()},
					{"want_alert_day", is_checked_want_alert_day()},
					{"checked_day", get_checked_day()},
					{"alert_in_holiday", !is_checked_dont_alert_in_holiday()}
				}
			);
		};
    }


	public void clear()
	{
		GetNode<LineEdit>("%TaskNameEdit").Clear();
		GetNode<SpinBox>("%Hour").Value = 0;
		GetNode<SpinBox>("%Minute").Value = 0;

		var day_checkbox_container = GetNode<HBoxContainer>("%DayCheckBoxContainer");
		foreach (var checkbox in day_checkbox_container.GetChildren())
		{
			(checkbox as CheckBox).ButtonPressed = false;
		}

		GetNode<CheckBox>("%IsDailyAlert").ButtonPressed = false;
		GetNode<CheckBox>("%CheckWantAlertDay").ButtonPressed = false;
		GetNode<CheckBox>("%DontAlertInHoliday").ButtonPressed = false;
	}


	private Dictionary get_task_alert_time()
	{
		var ampm_option_btn = GetNode<OptionButton>("%AMPM");
		var ampm_opt_index = ampm_option_btn.Selected;
		var ampm = ampm_option_btn.GetItemText(ampm_opt_index);
		
		var hour = (int)GetNode<SpinBox>("%Hour").Value;
		var minute = (int)GetNode<SpinBox>("%Minute").Value;

		return new Dictionary
		{
			{"ampm", ampm},
			{"hour", hour},
			{"minute", minute}
		};
	}

	private string get_task_name()
		=> GetNode<LineEdit>("%TaskNameEdit").Text;

	private bool is_checked_daily_alert()
		=> GetNode<CheckBox>("%IsDailyAlert").ButtonPressed;

	private bool is_checked_want_alert_day()
		=> GetNode<CheckBox>("%CheckWantAlertDay").ButtonPressed;

	private bool is_checked_dont_alert_in_holiday()
		=> GetNode<CheckBox>("%DontAlertInHoliday").ButtonPressed;


	private Dictionary<StringName, bool> get_checked_day()
	{
		var result = new Dictionary<StringName, bool>();
		var day_check_box_container = GetNode<HBoxContainer>("%DayCheckBoxContainer");
		var children = day_check_box_container.GetChildren();

		for (int i = 0; i < day_check_box_container.GetChildCount(); i += 1)
		{
			var child = children[i] as CheckBox;
			bool _checked = child.ButtonPressed;
			result[child.Name] = _checked;
		}

		return result;
	}


}
