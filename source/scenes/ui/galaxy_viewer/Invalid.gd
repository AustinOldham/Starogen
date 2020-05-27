extends Label

signal prevent_generate(value)

var invalid_dict = {}

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

# If the value is true, then the current input is invalid.
func _on_GalaxyViewer_invalid_check(type, value):
	invalid_dict[type] = value
	var invalid_array = invalid_dict.keys()
	var has_invalid = false
	for key in invalid_array:
		if (invalid_dict[key] == true):
			text = key + " is invalid"
			has_invalid = true
			break
	if (has_invalid):
		emit_signal("prevent_generate", true)
	else:
		emit_signal("prevent_generate", false)
		text = ""
		
