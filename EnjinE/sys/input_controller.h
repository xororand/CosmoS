#pragma once
#include <entt/entity/fwd.hpp>

class input_controller
{
public:
	static void step(entt::registry&);
private:
	static void keyboard_inputs(entt::registry&);
};

