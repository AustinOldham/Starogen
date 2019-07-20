extends Sprite

onready var planet_generator = preload("res://plugins/bin/PlanetGenerator.gdns").new()

func _ready():
	self.texture = planet_generator.get_planet()

#func _process(delta):
#	pass
