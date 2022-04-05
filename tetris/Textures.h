#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "common.h"

_NORA_BEGIN

enum class Texture {
	Background,
	Cell_Background,
	Cell_Piece,
};

class Textures
{
	std::map<nora::Texture, sf::Texture> m_textures;

public:
	Textures();
	sf::Texture& operator[] (nora::Texture index) {
		return m_textures[index];
	}
};
inline Textures textures;

_NORA_END