extends Node2D

const galaxy_star = preload("res://prototypes/galaxy/GalaxyStar.tscn")

func _ready():
	"""
	for i in range(500):
		for j in range(500):
			if (i % 10 == 0 and j % 10 == 0):
				var new_star = galaxy_star.instance()
				add_child(new_star)
				new_star.set_position(Vector2(i, j))
	"""
	"""
	for i in range(5000):
		for j in range(5000):
			if (i % 100 == 0 and j % 100 == 0):
				var new_star = galaxy_star.instance()
				add_child(new_star)
				new_star.set_position(Vector2(i, j))
				new_star.scale = Vector2(10, 10)
	"""
	for i in range(100):
		for j in range(100):
			#if (i % 100 == 0 and j % 100 == 0):
				var new_star = galaxy_star.instance()
				add_child(new_star)
				new_star.set_position(Vector2(i, j))
				#new_star.scale = Vector2(10, 10)
				new_star.get_node("Sprite").modulate = Color(i / 100.0, j/ 100.0,0)