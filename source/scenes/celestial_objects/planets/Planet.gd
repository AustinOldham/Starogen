extends KinematicBody2D


func _ready():
	$Area2D.connect("body_entered", self, "_on_Area2D_body_enter")
	$Area2D.connect("body_exited", self, "_on_Area2D_body_exit")


func _process(delta):
	rotation_degrees += 2.0 * delta
	pass

func _on_Area2D_body_enter(body):
	if (body.has_method("_set_gravity")):
		body._set_gravity(self)

func _on_Area2D_body_exit(body):
	if (body.has_method("_remove_gravity")):
		body._remove_gravity(self)	