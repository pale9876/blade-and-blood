using Godot;
using Godot.Collections;
using System;

public partial class Chrono : Node
{
	
	[Signal] public delegate void spendEventHandler();


	private Dictionary current_time;


	Chrono()
	{
		current_time = Time.GetDatetimeDictFromSystem();
	}


    public override void _Process(double delta)
    {
        var _current = Time.GetDatetimeDictFromSystem();
		var sec = (int)_current["second"];

		if (get_sec() != sec)
		{
			EmitSignalspend();
		}

		current_time = _current;
    }

	public string get_time_str()
	{
		var _hour = get_hour();
		var _min = get_min();
		var _sec = get_sec();
		
		string _cache = "";

		_cache += ((_hour / 10 < 1) ? "0" : "") + _hour.ToString() + ":";
		_cache += ((_min / 10 < 1) ? "0" : "") + _min.ToString() + ":";
		_cache += ((_sec / 10 < 1) ? "0" : "") + _sec.ToString();

		return _cache;
	}



	private int get_hour()
		=> (int)current_time["hour"];


	private int get_min()
		=> (int)current_time["minute"];


	private int get_sec()
		=> (int)current_time["second"];

}
