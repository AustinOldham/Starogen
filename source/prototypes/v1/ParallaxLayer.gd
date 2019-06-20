extends ParallaxLayer

func _ready():
	get_tree().get_root().connect("size_changed", self, "resize_background")
	#motion_mirroring = get_viewport_rect().size
	pass

func resize_background():
	#motion_mirroring = get_viewport_rect().size
	pass
