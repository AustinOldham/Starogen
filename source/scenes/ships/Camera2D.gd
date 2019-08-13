extends Camera2D

func _ready():
	pass

func _input(event):
	if event is InputEventMouseButton:
		if event.is_pressed():
			if event.button_index == BUTTON_WHEEL_UP:
				zoom_camera(-1)
			if event.button_index == BUTTON_WHEEL_DOWN:
				zoom_camera(1)
		if event.button_index == BUTTON_RIGHT and event.is_pressed():
			zoom += Vector2(10, 10)

func zoom_camera(direction):
	#print(global_scale)
	var temp = zoom + Vector2(0.1, 0.1) * direction
	if (temp.x <= 0.01 or temp.y <= 0.01):
		pass
	else:
		zoom = temp