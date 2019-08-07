extends Camera2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _process(delta):
	if (Input.is_action_pressed("ui_left")):
		global_position += Vector2(-0.1, 0.0)
	if (Input.is_action_pressed("ui_right")):
		global_position += Vector2(0.1, 0.0)

	if (Input.is_action_pressed("ui_up")):
		global_position += Vector2(0.0, 0.1)
	elif (Input.is_action_pressed("ui_down")):
		global_position += Vector2(0.0, -0.1)

