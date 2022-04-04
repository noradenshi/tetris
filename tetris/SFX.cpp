#include "SFX.h"

_NORA_BEGIN

SFX::SFX() {
	m_sounds[Sound::Move].loadFromFile("audio/unsure.wav");
	m_sounds[Sound::Rotate].loadFromFile("audio/flap.wav");
	m_sounds[Sound::Lock_0].loadFromFile("audio/point_ch1.ogg");
	m_sounds[Sound::Lock_1].loadFromFile("audio/point_ch2.ogg");
	m_sounds[Sound::Lock_2].loadFromFile("audio/point_ch3.ogg");
	m_sounds[Sound::Lock_3].loadFromFile("audio/point_ch4.ogg");
	m_sounds[Sound::Lock_4].loadFromFile("audio/point_ch5.ogg");
	m_sounds[Sound::Lock_5].loadFromFile("audio/point_ch6.ogg");
	//m_sounds[Sound::Lock].loadFromFile("audio/flap.wav");
	//m_sounds[Sound::Rotate].loadFromFile("audio/tetris rotation q.ogg");
	//m_sounds[Sound::Lock].loadFromFile("audio/tetris lock.ogg");

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