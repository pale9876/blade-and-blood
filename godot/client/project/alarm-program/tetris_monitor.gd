extends Node2D


@export var _tick_time: float = 1.
@export var size: Vector2i = Vector2(10, 20)
@export var tile_size: Vector2 = Vector2(32., 32.)
@export var autostart: bool = false


var engine: Tetris
var _tick: Timer


@onready var tetris: TileMapLayer = $CanvasLayer/Tetris


func _init() -> void:
	_tick = Timer.new()
	add_child(_tick)

	engine = Tetris.new()
	add_child(engine)

	_tick.timeout.connect(
		func() -> void:
			var result := engine.tick()
			_update(result["state"])
			_tick.start(_tick_time)
	)

	engine.init_cursor(Block.create_block(0))
	engine.init_prev(Block.create_block(0))


func _ready() -> void:
	if autostart:
		engine.resize(size)
		_tick.start(_tick_time)
	
	var _state: Array[PackedInt32Array] = engine.get_state()
	for y: int in _state.size():
		var _line: PackedInt32Array = _state[y]
		for x: int in _line.size():
			var _pos: Vector2i = Vector2i(x, y)
			if _line[x] == 0:
				tetris.set_cell(_pos, 0, Vector2i(0, 0), 1)
			else:
				tetris.set_cell(_pos, 0, Vector2i(0, 0), 2)


func _update(_state: Array[PackedInt32Array]) -> void:
	#var _state: Array[PackedInt32Array] = engine.get_state()
	for y: int in _state.size():
		var _line: PackedInt32Array = _state[y]
		for x: int in _line.size():
			var _pos: Vector2i = Vector2i(x, y)
			if _line[x] == 0:
				tetris.set_cell(_pos, 0, Vector2i(0, 0), 1)
			else:
				tetris.set_cell(_pos, 0, Vector2i(0, 0), 2)

	
