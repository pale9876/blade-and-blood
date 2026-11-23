using Godot;
using Godot.Collections;


public partial class ReservationList : TabBar
{


	public void create_attr(Dictionary data)
		=> GetNode<VBoxContainer>("VBoxContainer").AddChild(new TaskAttr(data));


	public partial class TaskAttr : HBoxContainer
	{
		private Label task_name;
		private Label ampm;
		private Label hour;
		private Label minute;
		private Button edit_btn;
		private Button delete_btn;


		public TaskAttr(Dictionary data)
		{
			Alignment = AlignmentMode.Center;

			// 작업명
			task_name = new Label{ Text = data["task_name"].As<string>() };

			// 시간설정
			var time_dict = data["time"].As<Dictionary>();
			
			ampm = new Label { Text = time_dict["ampm"].As<string>() };
			hour = new Label { Text = time_dict["hour"].As<int>().ToString() + "시" };
			minute = new Label { Text = time_dict["minute"].As<int>().ToString() + "분" };
			edit_btn = new Button { Text = "수정" };
			delete_btn = new Button { Text = "취소" };

			// 자식노드 추가
			AddChild(task_name);
			AddChild(ampm);
			AddChild(hour);
			AddChild(minute);
			AddChild(edit_btn);
			AddChild(delete_btn);
		}
	}
}
