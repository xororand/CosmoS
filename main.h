#pragma once
#include "core/game/game.h"
#include "Windows.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	game m_game;
	return m_game.run();
}

