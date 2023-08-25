#include "SFX.h"

_NORA_BEGIN

SFX::SFX() {
	m_sounds[Sound::Move].loadFromFile("resources/audio/ttr_move_mono.wav");
	m_sounds[Sound::Rotate].loadFromFile("resources/audio/flap.wav");
	m_sounds[Sound::Lock].loadFromFile("resources/audio/ttr_lock_mono.wav");
}

void SFX::play(nora::Sound t_sound, float t_pos) {
	float pan = t_pos - 0.5f;
	pan /= 2;
	// std::cout << "pan: " << pan << std::endl;
	m_sources[m_nextID].setAttenuation(10.f);
	m_sources[m_nextID].setMinDistance(1.f);
	m_sources[m_nextID].setRelativeToListener(true);
	m_sources[m_nextID].setPosition(pan, 0, pan < 0.f ? -pan - 1.f : pan - 1.f);

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
