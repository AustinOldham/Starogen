extends RigidBody2D

export (int) var rotation_speed = 180
export (int) var speed = 150
export (float) var acceleration = 0.10
export (float) var deceleration = 0.01
var current_direction = Vector2(0,0)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _physics_process(delta):
	if (Input.is_action_pressed("ui_left")):
		rotation_degrees -= rotation_speed * delta
	if (Input.is_action_pressed("ui_right")):
		rotation_degrees += rotation_speed * delta

	var new_direction = Vector2(1,0).rotated(rotation)

	if (Input.is_action_pressed("ui_up")):
		current_direction = current_direction.linear_interpolate(new_direction, acceleration)
	elif (Input.is_action_pressed("ui_down")):
		current_direction = current_direction.linear_interpolate(-new_direction, acceleration)
	else:
		current_direction = current_direction.linear_interpolate(Vector2(0,0), deceleration)

	#move_and_collide(current_direction * speed * delta)