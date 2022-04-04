#pragma once
#include <SFML/Audio.hpp>
#include <array>
#include <map>
#include "common.h"

_NORA_BEGIN

enum class Sound {
	Move,
	Rotate,
	Lock_0,
	Lock_1,
	Lock_2,
	Lock_3,
	Lock_4,
	Lock_5,
};

class SFX
{
	std::map<nora::Sound, sf::SoundBuffer> m_sounds;
	std::array<sf::Sound, 100> m_sources;
	int m_nextID = 0;

public:
	SFX();
	void play(nora::Sound t_sound);
	void setVolume(int t_val);
};
inline SFX sfx;

_NORA_END