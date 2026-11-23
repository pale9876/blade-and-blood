using Godot;
using Godot.Collections;


[GlobalClass]
public partial class PanelWindow : Window
{

	private PanelWindow()
	{

	}


    public override void _EnterTree()
    {
        base._EnterTree();

		_init_window();
    }


	private void _init_window()
	{
		init_window_pos(new Vector2I());
	}


	private Vector2I get_resolution() => new Vector2I(
		(int)ProjectSettings.GetSetting("display/window/size/viewport_width"),
		(int)ProjectSettings.GetSetting("display/window/size/viewport_height")
	);


	private void init_window_pos(Vector2I pos)
	{
		var cache = new Vector2I();

		for (int i = 0; i < DisplayServer.GetScreenCount(); i++)
			cache += DisplayServer.ScreenGetSize(i);
		
		var taskbar_height = WindowManager.get_screen_taskbar_height(0);
		var resolution = get_resolution();
		var current_screen_size = get_current_screen_size();
		Position = new Vector2I(
			cache.X - pos.X, current_screen_size.Y - pos.Y - taskbar_height
		);
	}


	private Vector2I get_current_screen_size() => DisplayServer.ScreenGetSize(GetWindow().CurrentScreen);


	
}
