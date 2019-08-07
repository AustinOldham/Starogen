extends Camera2D

func _ready():
	pass

func _input(event):
	if event is InputEventMouseButton:
		if event.is_pressed():
			# zoom in
			if event.button_index == BUTTON_WHEEL_UP:
				print("up")
				zoom_camera(-1)
			# zoom out
			if event.button_index == BUTTON_WHEEL_DOWN:
				print("down")
				zoom_camera(1)

func zoom_camera(direction):
	var temp = zoom + Vector2(0.1, 0.1) * direction
	if (temp.x <= 0.01 or temp.y <= 0.01):
		print("zero")
		print(temp)
	else:
		print("not")
		zoom = temp
		print(zoom)