using Godot;
using System;

public partial class MainScene : Node
{
	
	public override void _Ready()
    {
        base._Ready();
		
		get_task_reservation_ui().reserved += (data) =>
			get_reservation_list().create_attr(data);
    }

	private OpeningPanel get_opening_panel() => GetNode<OpeningPanel>("OpeningPanelWindow");

	private TaskReservationUI get_task_reservation_ui() => GetNode<TaskReservationUI>("%예약");
	private ReservationList get_reservation_list() => GetNode<ReservationList>("%리스트");

}
