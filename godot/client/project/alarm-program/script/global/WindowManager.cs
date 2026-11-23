using Godot;


public static class WindowManager
{
	static public Vector2I get_main_screen_size()
		=> DisplayServer.ScreenGetSize(0);


	static public int get_screen_taskbar_height(int idx)
		=> DisplayServer.ScreenGetSize(idx).Y - DisplayServer.ScreenGetUsableRect(idx).Size.Y;
}
