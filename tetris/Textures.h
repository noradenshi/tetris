#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "common.h"

_NORA_BEGIN

enum class Texture {
	Cell_Background,
	Cell_Piece,
	Background,
};

class Textures
{
	std::map<nora::Texture, sf::Texture> m_textures;

public:
	Textures() {
		m_textures[Texture::Background].loadFromFile("graphics/background.png");
		m_textures[Texture::Cell_Background].loadFromFile("graphics/block3.png");
		m_textures[Texture::Cell_Piece].loadFromFile("graphics/block2.png");
	}
	sf::Texture& operator[] (nora::Texture index) {
		return m_textures[index];
	}
};
inline Textures textures;

_NORA_END