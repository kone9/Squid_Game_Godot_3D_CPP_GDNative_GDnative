
#include "PlayerMovement.h"
#include <CanvasItem.hpp>
#include <InputEventMouseMotion.hpp>
#include <Viewport.hpp>

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

		register_method("MovePlayer", &PlayerMovement::MovePlayer);
		register_method("MovePlayerCamera", &PlayerMovement::MovePlayerCamera);
		register_method("CheckJumping", &PlayerMovement::CheckJumping);
		register_method("CheckMoving", &PlayerMovement::CheckMoving);
		register_method("CheckDeathTime", &PlayerMovement::CheckDeathTime);

		//Variables para ver en el editor
		register_property<PlayerMovement, float>("PlayerMovement", &PlayerMovement::Speed, 1);
		register_property<PlayerMovement, float>("Sensitivity", &PlayerMovement::Sensitivity, 1);
		register_property<PlayerMovement, float>("Jumpforce", &PlayerMovement::Jumpforce, 1);

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
		
		Godot::print("inicio el juegador con el player movement");
		Godot::print("proyecto funcionado correctamente");
	}

	void PlayerMovement::_process(const real_t delta)
	{
		if (isDying) {return;}
		float v = input->get_action_strength("w") - input->get_action_strength("s");//movimiento 
		float h = input->get_action_strength("a") - input->get_action_strength("d");//movimiento 

		PlayerMouseInput = get_viewport()->get_mouse_position();//posicion de mouse
		Godot::print(String::num_real(PlayerMouseInput.x));
		Godot::print(String::num_real(PlayerMouseInput.y));
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

	//para cambiar posicion de objetos físicos
	void PlayerMovement::_integrate_forces(const PhysicsDirectBodyState* state)
	{
		MovePlayerCamera();//muevo la camera
	}

	void PlayerMovement::_physics_process(const real_t delta)
	{
		MovePlayer();//muevo el personaje
		CheckJumping();//verifica si esta saltando
		CheckMoving();//verifiva si se mueve
	}

	void PlayerMovement::MovePlayer()
	{
		//		Vector3 MoveVector = transform.TransformDirection(PlayerMovementInput) * Speed;
		Vector3 move_vector_Horizontal = get_transform().basis.x * PlayerMovementInput.x * Speed;
		Vector3 move_vector_vertical = get_transform().basis.z * PlayerMovementInput.z * Speed;
		Vector3 MoveVector = move_vector_vertical + move_vector_Horizontal;//tiene que ser vector forward posiblemente aca tenga un error

//		PlayerBody.velocity = new Vector3(MoveVector.x, PlayerBody.velocity.y, MoveVector.z);
		set_linear_velocity(Vector3(MoveVector.x, -1, MoveVector.z));

		//if (Input.GetKeyDown(KeyCode.Space))
		if (input->is_action_just_pressed("click_izquierdo"))//para saltar
		{
			if (!isJumping)//sino estoy saltando
			{
				Godot::print("tendria que saltar");
				//PlayerBody.AddForce(Vector3.up * Jumpforce, ForceMode.Impulse);
				apply_impulse(get_translation(), Vector3::UP * Jumpforce);//aplico un impulso en la posición actual
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
		//PlayerCamera->set_rotation_degrees(Vector3(xRot + 45, 0, 0));//para rotar sobre el eje X
	}

	void PlayerMovement::CheckJumping()
	{

	}

	void PlayerMovement::CheckMoving()
	{

	}

	void PlayerMovement::CheckDeathTime()
	{
	}

} /* namespace godot */


