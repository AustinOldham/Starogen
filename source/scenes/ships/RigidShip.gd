extends RigidBody2D

export (int) var rotation_speed = 180
export (int) var speed = 150
export (float) var acceleration = 0.10
export (float) var deceleration = 0.01
var current_direction = Vector2(0,0)

# Called when the node enters the scene tree for the first time.
func _ready():
	#angular_damp = 10.0
	pass

func _physics_process(delta):
	if (Input.is_action_pressed("ui_left")):
		#rotation_degrees -= rotation_speed * delta
		add_torque(-rotation_speed * delta)
		#set_applied_torque(-rotation_speed)
	if (Input.is_action_pressed("ui_right")):
		add_torque(rotation_speed * delta)
		#set_applied_torque(rotation_speed)
	elif(!Input.is_action_pressed("ui_left")):
		_suppress_turning(delta)
		pass

	var new_direction = Vector2(1,0).rotated(rotation)

	if (Input.is_action_pressed("ui_up")):
		add_central_force(new_direction * acceleration)
		#current_direction = current_direction.linear_interpolate(new_direction, acceleration)
	elif (Input.is_action_pressed("ui_down")):
		add_central_force(-new_direction * acceleration)
		#current_direction = current_direction.linear_interpolate(-new_direction, acceleration)
	else:
		pass
		#current_direction = current_direction.linear_interpolate(Vector2(0,0), deceleration)
		if (applied_force.abs() > Vector2(0.0001, 0.0001)):
			add_central_force(-new_direction * acceleration)

	#move_and_collide(current_direction * speed * delta)

func _suppress_turning(delta):
	if (abs(applied_torque) > 0.0001):
		add_torque(-rotation_speed * delta * sign(applied_torque))
		#set_applied_torque(sign(applied_torque) * rotation_speed)
		#set_applied_torque(0)
		pass
	pass