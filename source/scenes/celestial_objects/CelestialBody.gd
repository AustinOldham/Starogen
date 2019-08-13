extends KinematicBody2D

class_name CelestialBody

var size
var seed_input
var orbiting_bodies = []
var orbit_distance
var orbit_speed


func _ready():
	pass

func _create_collision_polygon():
	#NOTE: This is probably very inefficient and was done this way due to simplicity. I might write an optimized version if performance becomes an issue.
	var bm = BitMap.new()
	bm.create_from_image_alpha($Sprite.texture.get_data())
	var rect = Rect2($Sprite.position.x, $Sprite.position.y, $Sprite.texture.get_width(), $Sprite.texture.get_height())
	var my_array = bm.opaque_to_polygons(rect, 0.0001)
	var offsetX = 0
	var offsetY = 0
	if ($Sprite.texture.get_width() % 2 != 0):
		offsetX = 1
	if ($Sprite.texture.get_height() % 2 != 0):
		offsetY = 1
	for i in range(my_array.size()):
		var my_collision = CollisionPolygon2D.new()
		#my_collision.set_build_mode(1)
		# Godot has a glitch that prevents collision with CollisionPolygon2Ds if they have overlapping vertices. This removes those overlapping parts and creates a new node for them.
		var temp_arr = Array(my_array[i])
		var duplicates = []
		for j in range(temp_arr.size()):
			var count = temp_arr.count(temp_arr[j])
			if (count > 1):
				duplicates.append(j)
		var duplicates_offset = 0
		for j in range(duplicates.size() / 2):
			var new_collision_points = []
			for k in range(duplicates[1] - duplicates[0]):
				new_collision_points.append(temp_arr[duplicates[0]])
				temp_arr.remove(duplicates[0])
			duplicates_offset += duplicates[1] - duplicates[0]
			duplicates.remove(0)
			duplicates.remove(0)
			var new_collision = CollisionPolygon2D.new()
			#new_collision.set_build_mode(1)
			new_collision.set_polygon(PoolVector2Array(new_collision_points))
			new_collision.position -= Vector2(($Sprite.texture.get_width() / 2) + offsetX, ($Sprite.texture.get_height() / 2) + offsetY) * self.scale.x
			new_collision.scale = self.scale
			call_deferred("add_child", new_collision)
		var new_arr = PoolVector2Array(temp_arr)
		my_collision.set_polygon(new_arr)
		my_collision.position -= Vector2(($Sprite.texture.get_width() / 2) + offsetX, ($Sprite.texture.get_height() / 2) + offsetY) * self.scale.x
		my_collision.scale = self.scale
		call_deferred("add_child", my_collision)