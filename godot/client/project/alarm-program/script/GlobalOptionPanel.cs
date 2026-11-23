using Godot;


public partial class GlobalOptionPanel : TabBar
{

	private Button get_apply_btn() => GetNode<Button>("%ApplySetting");


    public override void _Ready()
    {
        base._Ready();

		var _window = GetWindow();
		var _edit = get_res_edit();
		var init_size = _window.Size;

		_window.SizeChanged += () =>
		{
			_edit.X.Value = init_size.X;
			_edit.Y.Value = init_size.Y;
		};

		_edit.X.Value = init_size.X;
		_edit.Y.Value = init_size.Y;

		get_apply_btn().ButtonUp += () =>
			_reinit_window_resolution();
    }


	private (SpinBox X, SpinBox Y) get_res_edit()
		=> (GetNode<SpinBox>("%ResolutionX"), GetNode<SpinBox>("%ResolutionY"));


	private Vector2I _get_edited_resolution()
	{
		var _edit = get_res_edit();
		return new Vector2I((int)_edit.X.Value, (int)_edit.Y.Value);
	}


	private void _reinit_window_resolution()
		=> GetWindow().Size = _get_edited_resolution();


	ConfigFile _config;
	private void _save_settings()
	{
		var _config = new ConfigFile();

		// _config.SetValue("");
	}

}
