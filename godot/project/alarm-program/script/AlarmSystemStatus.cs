using Godot;
using System;
using System.Security.Cryptography.X509Certificates;

public partial class AlarmSystemStatus : StatusIndicator
{

	public AlarmSystemStatus()
	{
		Visible = true;
		Tooltip = "Hello";
		// create_menu();
		
		Pressed += (long mouse_btn, Vector2I pos) =>
		{
			if (mouse_btn == (long)MouseButton.Left)
			{
				Global.setting_ui_window.Visible = true;
			}
			else if (mouse_btn == (long)MouseButton.Right)
			{
				Global.menu.Popup(
					new Rect2I(DisplayServer.MouseGetPosition(), new Vector2I())
				);
			}
		};
	}


    public override void _EnterTree()
    {
        base._EnterTree();

		GetTree().AutoAcceptQuit = false;
	}


    public override void _Notification(int what)
    {
        base._Notification(what);

		if (what == NotificationWMCloseRequest)
		{
			Visible = false;
			QueueFree();
		}
    }

}
