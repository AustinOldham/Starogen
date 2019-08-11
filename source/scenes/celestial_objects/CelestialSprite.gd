extends Sprite

class_name CelestialSprite

func _ready():
	pass

func _create_collision_polygon():
	#NOTE: This is probably very inefficient and was done this way due to simplicity. I might write an optimized version if performance becomes an issue.
	var bm = BitMap.new()
	bm.create_from_image_alpha(self.texture.get_data())
	var rect = Rect2(self.position.x, self.position.y, self.texture.get_width(), self.texture.get_height())
	var my_array = bm.opaque_to_polygons(rect, 0.0001) #0.0001
	var my_polygon = Polygon2D.new()
	my_polygon.set_polygons(my_array)
	var offsetX = 0
	var offsetY = 0
	if (texture.get_width() % 2 != 0):
		offsetX = 1
	if (texture.get_height() % 2 != 0):
		offsetY = 1
	for i in range(my_polygon.polygons.size()):
		print("i: ", i)
		var my_collision = CollisionPolygon2D.new()
		# Godot has a glitch that prevents collision with CollisionPolygon2Ds if they have overlapping vertices
		var temp_arr = Array(my_polygon.polygons[i])
		var duplicates = []
		for j in range(temp_arr.size()):
			var count = temp_arr.count(temp_arr[j])
			if (count > 1):
				print("Duplicate at: ", j)
				print("Count: ", count)
				duplicates.append(j)
		#var duplicates_offset

		for j in range(duplicates.size() / 2):
			for k in range(duplicates[1] - duplicates[0]):
				print(temp_arr[duplicates[0]])
				temp_arr.remove(duplicates[0])
		var new_arr = PoolVector2Array(temp_arr)
		my_collision.set_polygon(new_arr)
		my_collision.position -= Vector2((self.texture.get_width() / 2) + offsetX, (self.texture.get_height() / 2) + offsetY) * self.scale.x
		my_collision.scale = self.scale
		get_parent().call_deferred("add_child", my_collision)