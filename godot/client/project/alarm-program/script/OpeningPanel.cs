using Godot;
using System;

public partial class OpeningPanel : CanvasLayer
{
	public override void _Ready()
	{
		var anim = GetNode<AnimationPlayer>("AnimationPlayer");
		anim.Play("opening");
		anim.AnimationFinished += (anim_name) =>
		{
			Global.right_down_panel.Visible = true;
			CallDeferred(MethodName.QueueFree);
		};
	}

}
