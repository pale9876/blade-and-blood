using Godot;
using System;

public partial class SettingUIWindow : Window
{

	public SettingUIWindow()
	{
		Global.setting_ui_window = this;

		
		Visible = false;

		CloseRequested += () =>
		{
			Visible = false;	
		};
	}

	
}
