extends Node2D

const galaxy_star = preload("res://prototypes/galaxy/GalaxyStar.tscn")

func _ready():
	for i in range(500):
		for j in range(500):
			if (i % 10 == 0 and j % 10 == 0):
				var new_star = galaxy_star.instance()
				add_child(new_star)
				new_star.set_position(Vector2(i, j))
