#include "MachineGun.h"

namespace godot
{
	MachineGun::MachineGun()
	{
	}

	MachineGun::~MachineGun()
	{
	}

	void MachineGun::_register_methods()
	{
		register_method("_ready", &MachineGun::_ready);
		register_method("_process", &MachineGun::_process);
	}

	void MachineGun::_init()
	{
	}

	void MachineGun::_ready()
	{
		Godot::print("creado machine gun");
	}

	void MachineGun::_process(real_t delta)
	{
	}

}