extends Sprite

onready var planet_generator = preload("res://plugins/PlanetGenerator/bin/PlanetGenerator.gdns").new()

func _ready():
	randomize()
	self.texture = planet_generator.getPlanet(int(rand_range(0, 2147483647)), 100)
	self.scale.x = 5
	self.scale.y = 5

#func _process(delta):
#	pass
