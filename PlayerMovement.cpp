
#include "PlayerMovement.h"
#include <CanvasItem.hpp>
#include <InputEventMouseMotion.hpp>
#include <Viewport.hpp>
#include <StaticBody.hpp>

namespace godot
{

	PlayerMovement::PlayerMovement()
	{
		// TODO Auto-generated constructor stub
		PlayerMovementInput = Vector3::ZERO;
		PlayerMouseInput = Vector2::ZERO;
		xRot = 0;

		//variable para tener en el editor referencia
		anim = nullptr;

		isJumping = false;
		isWalking = false;
		isMoving = false;
		isDying = false;
		isInDeathZone = false;

		//variable para ver en el editor colisicon
		FloorMask = 0;

		//para ver en el editor
		FeetTransform = Transform::IDENTITY;

		//para ver en el editor
		PlayerCamera = nullptr;

		//para ver en el editor
		//Rigidbody PlayerBody; NO ES NECESARIO REFERENCIA A EL MISMO ACA NO HAY COMPONENTES SINO NODOS

		//variable para ver en el editor
		Speed = 0;

		//variable para ver en el editor
		Sensitivity = 0;

		//variable para ver en el editor
		Jumpforce = 0;

		//variable para ver en el editor
		feetSteps = nullptr;
		//variable para ver en el editor
		shoot = nullptr;

		//variable para ver en el editor
		deathZone = nullptr;

		input = nullptr;
		PlayerCamera = nullptr;

		areaDetectarSuelo = nullptr;
	}

	PlayerMovement::~PlayerMovement()
	{
		// TODO Auto-generated destructor stub
	}

	void PlayerMovement::_register_methods()
	{
		//registro los m�todos
		register_method("_ready", &PlayerMovement::_ready);
		register_method("_process", &PlayerMovement::_process);
		register_method("_physics_process", &PlayerMovement::_physics_process);
		register_method("_integrate_forces", &PlayerMovement::_integrate_forces);

		//funciones del juego
		register_method("MovePlayer", &PlayerMovement::MovePlayer);
		register_method("MovePlayerCamera", &PlayerMovement::MovePlayerCamera);
		register_method("CheckJumping", &PlayerMovement::CheckJumping);
		register_method("CheckMoving", &PlayerMovement::CheckMoving);
		register_method("CheckDeathTime", &PlayerMovement::CheckDeathTime);

		//Variables para ver en el editor
		register_property<PlayerMovement, float>("PlayerMovement", &PlayerMovement::Speed, 1);
		register_property<PlayerMovement, float>("Sensitivity", &PlayerMovement::Sensitivity, 1);
		register_property<PlayerMovement, float>("Jumpforce", &PlayerMovement::Jumpforce, 1);

		//Senials
		register_method("_on_AreaDetectarSuelo_area_entered", &PlayerMovement::_on_AreaDetectarSuelo_area_entered);

	}

	void PlayerMovement::_init()
	{
	}

	void PlayerMovement::_ready()
	{
		input = Input::get_singleton();//obtener el input
		input->set_mouse_mode(input->MOUSE_MODE_CAPTURED);
		input->set_mouse_mode(input->MOUSE_MODE_VISIBLE);
		PlayerCamera = get_node<Camera>("Camera");//obtener la camara
		areaDetectarSuelo = get_node<Area>("AreaDetectarSuelo");//obtener la camara

		
		Godot::print("inicio el juegador con el player movement");
		Godot::print("proyecto funcionado correctamente");
		Godot::print("proyecto funcionado correctamente");
		
	}

	void PlayerMovement::_process(const real_t delta)
	{
		if (isDying) {return;}
		float v = input->get_action_strength("w") - input->get_action_strength("s");//movimiento 
		float h = input->get_action_strength("a") - input->get_action_strength("d");//movimiento 
		
		PlayerMouseInput = get_viewport()->get_mouse_position();//posicion de mouse
		PlayerMovementInput = Vector3(h, 0, v);//para obtener el input y luego mover

		isWalking = (h != 0 || v != 0);//si es distinto de cero me estoy moviendo
//		anim.SetBool("isWalking", isWalking);//activo animacion caminar

		//if (isWalking && !isJumping && !feetSteps->is_playing())//si estoy caminando y no estoy saltando y no se esta reproduciendo el sonido
		//{
		//				//feetSteps->play();//sonido feetSteps
		//}
		//else
		//{
		//				//feetSteps->stop();//sonido feetSteps Stop
		//}

		CheckDeathTime();//tiene que ver con el tiempo, capas modifico por tiemr
	}

	void PlayerMovement::_physics_process(const real_t delta)
	{
		MovePlayer();//muevo el personaje
		CheckMoving();//verifiva si se mueve, si salta o camina se esta moviendo
	}

	//para cambiar posicion de objetos físicos
	void PlayerMovement::_integrate_forces(const PhysicsDirectBodyState* state)
	{
		MovePlayerCamera();//muevo la camera
	}

	void PlayerMovement::_on_AreaDetectarSuelo_area_entered(Area* area)
	{
		if (area->is_in_group("Suelo"))
		{
			isJumping = false;
		}
	}

	
	void PlayerMovement::MovePlayer()
	{
		//		Vector3 MoveVector = transform.TransformDirection(PlayerMovementInput) * Speed;
		
		Vector3 move_vector_Horizontal = get_transform().basis.x * PlayerMovementInput.normalized().x * Speed;
		Vector3 move_vector_vertical = get_transform().basis.z * PlayerMovementInput.normalized().z * Speed;
		Vector3 MoveVector = move_vector_vertical + move_vector_Horizontal;//tiene que ser vector forward posiblemente aca tenga un error

//		PlayerBody.velocity = new Vector3(MoveVector.x, PlayerBody.velocity.y, MoveVector.z);
		set_linear_velocity(Vector3(MoveVector.x, -3, MoveVector.z));
		
		//if (Input.GetKeyDown(KeyCode.Space))
		if (input->is_action_just_pressed("click_izquierdo"))//para saltar
		{
			if (!isJumping)//sino estoy saltando
			{
				Godot::print("tendria que saltar");
				//PlayerBody.AddForce(Vector3.up * Jumpforce, ForceMode.Impulse);
				CheckJumping();
			}
		}
	}

	void PlayerMovement::MovePlayerCamera()
	{
		//xRot -= PlayerMouseInput.y * Sensitivity;
		xRot = -PlayerMouseInput.y * Sensitivity;
		
		//transform.Rotate(0f, PlayerMouseInput.x * Sensitivity, 0f);
		set_rotation_degrees(Vector3(0, -PlayerMouseInput.x * Sensitivity, 0));//rota sobre el eje y el personaje

//		PlayerCamera.transform.localRotation = Quaternion.Euler(xRot, 0f, 0f);
		PlayerCamera->set_rotation_degrees( Vector3(
				xRot,
				PlayerCamera->get_rotation_degrees().y,
				PlayerCamera->get_rotation_degrees().z
			)
		);//para rotar sobre el eje X
	}
	
	//verifica el salto como verdadero, aplica impulso y activa animacion
	void PlayerMovement::CheckJumping()
	{
		//isJumping = !Physics.CheckSphere(FeetTransform.position, 0.1f, FloorMask);//para detectar el suelo
		//USO el area que esta más arriba para evitar el doble salto
		isJumping = true;//estoy saltando
		apply_central_impulse(Vector3::UP * Jumpforce);//impulso desde el centro
		//anim.SetBool("isJumping", isJumping);
		//animacion saltar
	}

	void PlayerMovement::CheckMoving()//verifica si se mueve
	{
		isMoving = isJumping || isWalking;//si esta caminando o esta saltando se esta movimiendo
	}

	//verifica si se termino el tiempo y mata al jugador
	void PlayerMovement::CheckDeathTime()
	{

	}

} /* namespace godot */


