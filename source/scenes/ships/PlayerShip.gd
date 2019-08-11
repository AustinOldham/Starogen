# Copyright (C) 2019  Austin Oldham
#
# This file is part of Starogen.
#
# Starogen is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Starogen is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Starogen.  If not, see <https://www.gnu.org/licenses/>.

extends Ship

var gravity_array = []

func _ready():
	#add_to_group("movable")
	pass

func _physics_process(delta):
	if (Input.is_action_pressed("ui_left")):
		rotation_degrees -= rotation_speed * delta
	if (Input.is_action_pressed("ui_right")):
		rotation_degrees += rotation_speed * delta

	var new_direction = Vector2(1,0).rotated(rotation)
	
	#Add option to toggle between the += and linear_interpolate versions

	if (Input.is_action_pressed("ui_up")):
		#current_direction = current_direction.linear_interpolate(new_direction, acceleration)
		current_direction += (new_direction * acceleration)
	elif (Input.is_action_pressed("ui_down")):
		current_direction = current_direction.linear_interpolate(-new_direction, acceleration)
	else:
		pass
		#current_direction = current_direction.linear_interpolate(Vector2(0,0), deceleration)

	current_direction = _apply_gravity(current_direction)
	#speed = _apply_rotation(speed)
	
	var temp_current_direction = current_direction * speed
	
	#temp_current_direction += get_floor_velocity()
	
	#for i in get_slide_count():
		#current_direction += get_slide_collision(i).collider_velocity
		#print(get_slide_collision(i).collider.name)
	
	#temp_current_direction *= speed

	#move_and_collide(current_direction * speed * delta)
	var collision = move_and_collide(temp_current_direction * delta)
	#move_and_slide(current_direction * speed)
	#var collision = move_and_slide(temp_current_direction)

	#_bounce(collision)
	


func _sharp_stop(new_direction):
	return current_direction.linear_interpolate(-new_direction, acceleration)

func _apply_rotation(speed):
	for i in range(gravity_array.size()):
		pass
		#speed -= (get_global_transform().origin - gravity_array[i].get_global_transform().origin).cross(Vector2(2, 2))
	return speed

func _bounce(collision):
	if collision:
		var reflect = collision.remainder.bounce(collision.normal)
		current_direction = current_direction.bounce(collision.normal)
		move_and_collide(reflect)	

func _apply_gravity(current_direction):
	#print("applied gravity")
	for i in range(gravity_array.size()):
		var new_gravity = get_global_transform().origin.direction_to(gravity_array[i].get_global_transform().origin)
		#current_direction = current_direction.linear_interpolate(new_gravity, 0.01)
		current_direction += (new_gravity * 0.01)
	return current_direction

func _set_gravity(the_planet):
	gravity_array.append(the_planet)
	print("set gravity")
	#print(body_position)
	#print(get_global_transform().origin)
	#gravity_array[index] = body_position

func _remove_gravity(the_planet):
	gravity_array.erase(the_planet)
	print("remove gravity")
	#gravity_array[index] = Vector2(0, 0)
