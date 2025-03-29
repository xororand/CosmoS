#pragma once
#include <comp/RenderScene.h>

#include "core/includes.h"

class render
{
public:
	static void frame(RenderScene& rs);
private:
	static void render_physics(RenderScene rs);
	static void set_controllable_view(RenderScene rs);
};

