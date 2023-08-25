#include "Textures.h"

_NORA_BEGIN

Textures::Textures()
{
	m_textures[Texture::Background].loadFromFile("resources/graphics/background.png");
	m_textures[Texture::Cell_Background].loadFromFile("resources/graphics/block3.png");
	m_textures[Texture::Cell_Piece].loadFromFile("resources/graphics/block2_n.png");
};

_NORA_END
