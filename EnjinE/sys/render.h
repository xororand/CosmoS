#pragma once
#include <comp/RenderScene.h>

#include "core/includes.h"

class render
{
public:
	static void frame();
private:
	static void render_physics();
	static void set_controllable_view();
};

