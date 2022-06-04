#pragma once
#include <SFML/Audio.hpp>
#include <array>
#include <map>
#include "common.h"
#include <iostream>

_NORA_BEGIN

enum class Sound {
	Move,
	Rotate,
	Lock
};

class SFX
{
	std::map<nora::Sound, sf::SoundBuffer> m_sounds;
	std::array<sf::Sound, 100> m_sources;
	int m_nextID = 0;

public:
	SFX();
	void play(nora::Sound t_sound, float t_pos = 0.f);
	void setVolume(int t_val);
};
inline SFX sfx;

_NORA_END