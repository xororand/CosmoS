#pragma once
#include <entt/entity/fwd.hpp>

class input_controller
{
public:
	static void step();
private:
	static void keyboard_inputs();
};

