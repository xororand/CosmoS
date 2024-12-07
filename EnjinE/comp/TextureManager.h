#pragma once

#include <map>
#include <filesystem>

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

namespace fs = std::filesystem;

class Game;

class TextureManager
{
private:
	// TODO: LOADING ALL TEXTURES COMPILTED TO ATLASES
	std::map<std::wstring, sf::Texture*> m_textures;
	std::vector<std::wstring> m_order;
public:
	TextureManager();

	sf::Texture* getTexture(std::wstring name);
	// Get texutre by index in map, or return null
	sf::Texture* getTexture(int index);

	void loadTexturesFromRootResources(fs::path dir = fs::current_path() / L"Resources\\Textures");

};

