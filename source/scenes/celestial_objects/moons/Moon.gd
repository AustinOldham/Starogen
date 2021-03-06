extends CelestialBody

onready var planet_generator = preload("res://plugins/PlanetGenerator/bin/PlanetGenerator.gdns").new()

func _ready():
	$GravitationalField.connect("body_entered", self, "_on_GravitationalField_body_enter")
	$GravitationalField.connect("body_exited", self, "_on_GravitationalField_body_exit")
	size = 20
	randomize()
	seed_input = int(rand_range(0, 2147483647))
	#scale = Vector2(5, 5)
	#scale = Vector2(20, 20)
	#scale = Vector2(100, 100)
	#scale = Vector2(50, 50)
	_generate()
	get_node("GravitationalField/CollisionShape2D").shape.radius = size
	#get_node("GravitationalField").scale = scale
	#$Sprite.scale = scale

func adjust_scale(new_scale):
	pass

func _physics_process(delta):
	rotation_degrees += 2.0 * delta
	pass

func _generate():
	var seed_input = int(rand_range(0, 2147483647))
	print(seed_input)
	$Sprite.texture = planet_generator.getPlanet(seed_input, size)	
	_create_collision_polygon()

func _calculate_orbits(delta):
	pass

func _on_GravitationalField_body_enter(body):
	if (body.has_method("_set_gravity")):
		body._set_gravity(self)

func _on_GravitationalField_body_exit(body):
	if (body.has_method("_remove_gravity")):
		body._remove_gravity(self)

func is_working():
	print("Moon is working")

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.is_pressed():
			print("Mouse Position: ", get_global_mouse_position())
			print("Distance: ", get_global_mouse_position().distance_to(global_position))