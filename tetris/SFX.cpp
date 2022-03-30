#include "SFX.h"

_NORA_BEGIN

SFX::SFX() {
	m_sounds[Sound::Rotate].loadFromFile("audio/tetris rotation q.ogg");
	m_sounds[Sound::Move].loadFromFile("audio/tetris move.ogg");
	m_sounds[Sound::Lock].loadFromFile("audio/tetris lock.ogg");

	setVolume(50);
}

void SFX::play(nora::Sound t_sound) {
	m_sources[m_nextID].setBuffer(m_sounds[t_sound]);
	m_sources[m_nextID].play();
	m_nextID++;
	if (m_nextID >= m_sources.size()) m_nextID = 0;
}

void SFX::setVolume(int t_val) {
	for (auto& source : m_sources) {
		source.setVolume(t_val);
	}
}

_NORA_END