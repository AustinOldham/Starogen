extends LineEdit

func _ready():
	pass



func _on_LineEdit_text_entered(new_text):
	UserPreferences.current_galaxy = new_text
	get_tree().change_scene("res://scenes/ui/galaxy_viewer/GalaxyMapViewer.tscn")
