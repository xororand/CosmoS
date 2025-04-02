#pragma once
#include "../defines.h"
#include "../includes.h"

#include "comp/TextureManager.h"
#include "comp/RenderScene.h"
#include "core/ChunkSystem/ChunkSystem.h"

class game
{

public:
	static inline entt::registry	reg;
	static inline TextureManager	texmngr;
	static inline RenderScene		rs;
	static inline ChunkSystem		cs;

	game();
	~game();

	int run();
};

