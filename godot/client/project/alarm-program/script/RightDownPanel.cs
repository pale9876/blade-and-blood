using Godot;


public partial class RightDownPanel : CanvasLayer
{
	public RightDownPanel()
	{
		Global.right_down_panel = this;
		
		Visible = false;

		VisibilityChanged += () =>
		{
			if (Visible)
				GetNode<Control>("Control").Visible = true;
		};
	}

    public override void _EnterTree()
    {
        base._EnterTree();

		var chrono = get_chrono();
		chrono.spend += () =>
		{
			var time_str = chrono.get_time_str();
			GetNode<Label>("%TimeLabel").Text = time_str;
		};
    }

	private Chrono get_chrono() => GetNode<Chrono>("/root/Chrono");


}
