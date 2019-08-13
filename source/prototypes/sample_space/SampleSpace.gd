extends Node2D

const ship_class = preload("res://scenes/ships/Ship.gd")
const celestial_class = preload("res://scenes/celestial_objects/CelestialBody.gd")

var bodies = []
var ships = []

func _ready():
	get_tree().paused = true
	_get_collidables(self)
	for ship in ships:
		var collision_count = 1
		while (collision_count > 0):
			print(collision_count)
			collision_count = 0
			for body in bodies:
				print("body.name: ", body.name)
				print("Ship position: ", ship.global_position)
				print("Body position: ", body.global_position)
				var distance = ship.global_position.distance_to(body.global_position)
				print("Distance: ", distance)
				print("body.size * body.scale.x * 10.0 * 2.0: ", body.size * body.scale.x * 10.0 * 2.0)
				if (distance < (body.size * body.scale.x * 10.0 * 2.0)):
					ship.set_global_position(Vector2(ship.global_position.x + (body.size * body.scale.x * 10.0), ship.global_position.y)) 
					collision_count += 1
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