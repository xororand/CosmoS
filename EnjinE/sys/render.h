#pragma once
#include <comp/RenderScene.h>

#include "core/includes.h"

class render
{
public:
	static void frame(entt::registry&, RenderScene rs);
};

