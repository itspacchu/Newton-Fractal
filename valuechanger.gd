extends ColorRect

#sliders
var root1x = null;
var root2x = null;
var root2y = null;
var root1y = null;
var root3x = null;
var root3y = null;

#colors
var C1 = null
var C2 = null
var C3 = null

#movement
var MoveCoord:Vector2 = Vector2.ZERO;
var zoom:float = 1.0;


func _ready() -> void:
	root1x = $local/root1x
	root2x = $local/root2x
	root2y = $local/root2y
	root1y = $local/root1y
	root3x = $local/root3x
	root3y = $local/root3y
	C1 = $local/C1
	C2 = $local/C3
	C3 = $local/C2
	MoveCoord = material.get_shader_param("coordMove")
	zoom = material.get_shader_param("zoom")

func _process(delta: float) -> void:
	material.set_shader_param("root1",Vector2(root1x.value/10,root1y.value/10))
	material.set_shader_param("root2",Vector2(root2x.value/10,root2y.value/10))
	material.set_shader_param("root3",Vector2(root3x.value/10,root3y.value/10))
	material.set_shader_param("color1",Vector3(C1.color.r,C1.color.g,C1.color.b))
	material.set_shader_param("color2",Vector3(C2.color.r,C2.color.g,C2.color.b))
	material.set_shader_param("color3",Vector3(C3.color.r,C3.color.g,C3.color.b))
	var hori = Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left")
	var verti = Input.get_action_strength("ui_up") - Input.get_action_strength("ui_down")
	var zoomin = Input.get_action_strength("ui_page_up") - Input.get_action_strength("ui_page_down")
	if(abs(zoomin) > 0):
		zoom += zoomin*delta
		material.set_shader_param("zoom",zoom)
		print(zoom)
	if(abs(hori + verti) > 0.001):
		MoveCoord += delta*Vector2(hori,verti)
		material.set_shader_param("coordMove",MoveCoord)
	
	
	
	
	
	
