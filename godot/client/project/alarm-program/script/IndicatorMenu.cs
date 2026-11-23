using Godot;


public partial class IndicatorMenu : PopupMenu
{

	const string ID_예약패널열기 = "예약 패널 열기";
	const string ID_종료 = "종료";


	public IndicatorMenu()
	{
		Global.menu = this;

		Visible = false;

		AddItem(ID_예약패널열기, 0);

		AddSeparator("", 1);
		SetItemDisabled(1, true);

		AddItem(ID_종료, 2);
		// AddItem("파르릇", 3);

		IdPressed += (id) =>
		{
			switch (GetItemText((int)id))
			{
				case ID_예약패널열기:
					Global.setting_ui_window.Visible = true;
					break;
				
				case ID_종료:
					GetTree().Quit();
					break;
			}
		};

	}


	private void add_separator(int index, string text)
	{
		AddSeparator(text, index);
		SetItemDisabled(index, true);
	}

}
