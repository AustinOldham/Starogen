extends CanvasLayer

func _ready():
	$MarginContainer/VBoxContainer/MenuOptions/Continue.connect("pressed", self, "continue_game")
	$MarginContainer/VBoxContainer/MenuOptions/NewGame.connect("pressed", self, "new_game")
	$MarginContainer/VBoxContainer/MenuOptions/Options.connect("pressed", self, "options")
	$MarginContainer/VBoxContainer/MenuOptions/Credits.connect("pressed", self, "credits")
	$MarginContainer/VBoxContainer/MenuOptions/Quit.connect("pressed", self, "quit_game")

func continue_game():
	get_tree().change_scene("res://prototypes/v1/SampleSpace.tscn")

func new_game():
	get_tree().change_scene("res://prototypes/v1/SampleSpace.tscn")

func options():
	pass

func credits():
	pass

func quit_game():
	get_tree().quit()
