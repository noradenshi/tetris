#include "Textures.h"

_NORA_BEGIN

Textures::Textures()
{
	m_textures[Texture::Background].loadFromFile("graphics/background.png");
	m_textures[Texture::Cell_Background].loadFromFile("graphics/block3.png");
	m_textures[Texture::Cell_Piece].loadFromFile("graphics/block2.png");
};

_NORA_END