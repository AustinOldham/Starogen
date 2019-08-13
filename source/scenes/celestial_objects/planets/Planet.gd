extends CelestialBody

onready var planet_generator = preload("res://plugins/PlanetGenerator/bin/PlanetGenerator.gdns").new()
const Moon = preload("res://scenes/celestial_objects/moons/Moon.tscn")

func _ready():
	$GravitationalField.connect("body_entered", self, "_on_GravitationalField_body_enter")
	$GravitationalField.connect("body_exited", self, "_on_GravitationalField_body_exit")
	size = 100
	randomize()
	seed_input = int(rand_range(0, 2147483647))
	#scale = Vector2(5, 5)
	#scale = Vector2(20, 20)
	#scale = Vector2(100, 100)
	#scale = Vector2(50, 50)
	#scale = Vector2(25, 25)
	_generate()
	get_node("GravitationalField/CollisionShape2D").shape.radius = size
	get_node("GravitationalField").scale = scale
	$Sprite.scale = scale
	_add_moon()
	#print(get_child_count())
	#print("Planet")

func _add_moon():
	print("Moon creation")
	var some_moon = Moon.instance()
	add_child(some_moon)
	some_moon.orbit_distance = 200 * scale.x
	some_moon.orbit_speed = 10.0
	some_moon.is_working()
	orbiting_bodies.append(some_moon)
	print("Moon path: ", some_moon.get_path())
	print("Moon size: ", some_moon.size)
	#print(some_moon.get_child_count())

func _physics_process(delta):
	rotation_degrees += 0.5 * delta
	_calculate_orbits(delta)
	pass

func _generate():
	var seed_input = int(rand_range(0, 2147483647))
	print(seed_input)
	$Sprite.texture = planet_generator.getPlanet(seed_input, size)	
	_create_collision_polygon()

func _calculate_orbits(delta):
	for body in orbiting_bodies:
		var x = body.orbit_distance * cos(delta * body.orbit_speed)# + get_global_position().x
		var y = body.orbit_distance * sin(delta * body.orbit_speed)# + get_global_position().y
		body.set_position(Vector2(x, y))

func _on_GravitationalField_body_enter(body):
	if (body.has_method("_set_gravity")):
		body._set_gravity(self)

func _on_GravitationalField_body_exit(body):
	if (body.has_method("_remove_gravity")):
		body._remove_gravity(self)	