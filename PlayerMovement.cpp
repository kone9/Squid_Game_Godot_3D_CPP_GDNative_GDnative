
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
		isInDeathZone = true;

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

		canMove = true;
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
		register_method("_input", &PlayerMovement::_input);

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
		register_method("_on_AreaDetectarSuelo_area_exited", &PlayerMovement::_on_AreaDetectarSuelo_area_exited);

	}

	void PlayerMovement::_init()
	{
	}

	void PlayerMovement::_ready()
	{
		input = Input::get_singleton();//obtener el input
		input->set_mouse_mode(input->MOUSE_MODE_CAPTURED);
		//input->set_mouse_mode(input->MOUSE_MODE_VISIBLE);
		PlayerCamera = get_node<Camera>("Camera");//obtener la camara
		areaDetectarSuelo = get_node<Area>("AreaDetectarSuelo");//obtener la camara
	}

	void PlayerMovement::_process(const real_t delta)
	{
		if (isDying) {return;}
		float v = input->get_action_strength("w") - input->get_action_strength("s");
		float h = input->get_action_strength("a") - input->get_action_strength("d");
		
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

	//input event de Godot
	void PlayerMovement::_input(const Ref<InputEvent> event)
	{
		//forma con mouse position
		//PlayerMouseInput = get_viewport()->get_mouse_position() ;//posicion de mouse
		//PlayerMouseInput.x -= (get_viewport()->get_visible_rect().get_size().x / 2);
		//PlayerMouseInput.y -= (get_viewport()->get_visible_rect().get_size().y / 2);
		//Godot::print(String::num_real(get_viewport()->get_mouse_position(). y));
		//Godot::print(String::num_real(get_viewport()->get_visible_rect().get_size().x));
		
		//forma con input mouse event motion
		if ( event->is_class("inputeventmousemotion") )//si el evento esta en la clase inputeventmousemotion
		{
			Godot::print("moviendo el mouse");
			InputEventMouseMotion *mouseMove = cast_to<InputEventMouseMotion>(*event);
			
			PlayerMouseInput.x += mouseMove->get_relative().x;
			PlayerMouseInput.y += mouseMove->get_relative().y;
			Godot::print(String::num_real( mouseMove->get_relative().x ));
			Godot::print(String::num_real( mouseMove->get_relative().y ));
			
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


	void PlayerMovement::_on_AreaDetectarSuelo_area_entered(Area* area)
	{
		if (area->is_in_group("Suelo"))
		{
			isJumping = false;
		}

		if (area->is_in_group("BotArea"))
		{
			canMove = false;
		}

	}

	void PlayerMovement::_on_AreaDetectarSuelo_area_exited(Area* area)
	{
		if (area->is_in_group("BotArea"))
		{
			canMove = true;
		}
	}


} /* namespace godot */


