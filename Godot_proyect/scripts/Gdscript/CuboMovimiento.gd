extends MeshInstance

export var aumentarVelocidad = 1
export var vel_mov : float = 1
export var max_X : float = 1.0
export var min_X :float = 1.0

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var mov : Vector3 = translation
	mov.x += vel_mov * (delta * aumentarVelocidad) 
	if mov.x > max_X:
		vel_mov *= -1
	elif mov.x < min_X:
		vel_mov *= -1
	translation = mov
	print(vel_mov)

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


