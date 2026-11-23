using Godot;
using Godot.Collections;


public partial class MaitreD : Node
{
	private const string PATH = "user://reservaitons.save";

	private Dictionary<string, string> _list;

	private MaitreD()
	{
		_list = new Dictionary<string, string>();

		_load_alarms();
	}


	private void _load_alarms()
	{
		if (FileAccess.FileExists(PATH))
		{
			GD.PrintErr("세이브 파일이 존재하지 않습니다.");
			GD.Print("그럼 뭐... 새로 하나 만들죠.");
		}

		using var _loaded = FileAccess.Open(PATH, FileAccess.ModeFlags.Read);

	}

	private void _save_reservations()
	{
		using var file = FileAccess.Open(PATH, FileAccess.ModeFlags.Write);

		file.StoreLine(Json.Stringify(_list));
	}



	public partial class AlarmInformation : Resource
	{
		
	}

}
