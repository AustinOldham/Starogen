extends StaticBody2D

var planet_index = 0 #Used to determine which planet's gravity is affecting a ship. (Change default to -1)

# Called when the node enters the scene tree for the first time.
func _ready():
	$Area2D.connect("body_entered", self, "_on_Area2D_body_enter")
	$Area2D.connect("body_exited", self, "_on_Area2D_body_exit")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#rotation_degrees += 2.0 * delta
	pass

func _on_Area2D_body_enter(body):
	if (body.has_method("_set_gravity")):
		body._set_gravity(self)

func _on_Area2D_body_exit(body):
	if (body.has_method("_remove_gravity")):
		body._remove_gravity(self)	