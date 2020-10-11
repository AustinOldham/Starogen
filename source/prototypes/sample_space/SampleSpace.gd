extends Node2D

const ship_class = preload("res://scenes/ships/Ship.gd")
const celestial_class = preload("res://scenes/celestial_objects/CelestialBody.gd")

var bodies = []
var ships = []

func _ready():
	get_tree().paused = true
	_get_collidables(self)
	_start_orbits()
	for ship in ships:
		var collision_count = 1
		while (collision_count > 0):
			print(collision_count)
			collision_count = 0
			for body in bodies:
				print("body.name: ", body.name)
				print("body.size: ", body.size)
				print("body.scale.x: ", body.scale.x)
				print("body.global_scale ", body.global_scale)
				print("Ship position: ", ship.global_position)
				print("Body position: ", body.global_position)
				var distance = ship.global_position.distance_to(body.global_position)
				var num = body.size * body.scale.x * 0.9
				print("Distance: ", distance)
				print("num: ", num)
				if (distance < num):
					print("Adjusted position")
					ship.set_global_position(Vector2(ship.global_position.x + (num), ship.global_position.y)) 
					collision_count += 1
				print("\n")
		#ship.intersecting = false
	get_tree().paused = false

func _get_collidables(node):
	for collidable in node.get_children():
		_get_collidables(collidable)
		if collidable is ship_class:
			print("Ship added: ", collidable.name)
			ships.append(collidable)
		elif collidable is celestial_class:
			print("Celestial added: ", collidable.name)
			bodies.append(collidable)

func _start_orbits():
	for node in bodies:
		node._calculate_orbits(0)

