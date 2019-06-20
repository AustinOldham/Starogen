extends TextureRect

func _ready():
	get_tree().get_root().connect("size_changed", self, "resize_background")
	rect_size = get_viewport_rect().size

func resize_background():
	rect_size = get_viewport_rect().size