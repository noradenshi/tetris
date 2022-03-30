#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <list>
#include <map>
#include <functional>
#include <algorithm>
#include "common.h"

_NORA_BEGIN

enum class Sound {
	Rotate,
	Move,
	Lock,
};

typedef std::function<void(int)> sound_callback_t;

class SoundThread {
	const int id;
	sf::Sound m_sound;
	sf::Thread m_thread = sf::Thread(&SoundThread::run, this);
	sound_callback_t m_callback;

	void run() {
		while (true) {
			if (m_sound.getStatus() != sf::Sound::Status::Playing) {
				m_callback(id);
				return;
			}
		}
	}
public:
	SoundThread(int t_id, sf::SoundBuffer& t_buffer, sound_callback_t& t_callback) : id(t_id) {
		m_sound.setBuffer(t_buffer);
		m_sound.play();
		m_thread.launch();
		m_callback = t_callback;
	}
	~SoundThread() {
		m_thread.terminate();
	}
	int getID() {
		return id;
	}
	bool operator == (const SoundThread& rhs) const {
		return this->id == rhs.id;
	}
	bool operator != (const SoundThread& rhs) const {
		return this->id != rhs.id;
	}
	bool operator == (const int& rhs) const {
		return this->id == rhs;
	}
	bool operator != (const int& rhs) const {
		return this->id != rhs;
	}
};

class SFX
{
	std::map<nora::Sound, sf::SoundBuffer> m_sounds;
	std::list<nora::SoundThread> m_sources;
	sf::Thread m_thread = sf::Thread(&SFX::removeTask, this);
	std::vector<int> m_removable;
	int m_nextID = 0;

	sound_callback_t callback_f = [&m_removable = m_removable](int t_id) {
		m_removable.push_back(t_id);
	};
	void removeTask() {
		while (true) {
			//yes:
			sf::sleep(sf::seconds(1));
			for (std::vector<int>::iterator it = m_removable.begin(); it != m_removable.end(); ++it) {
				auto result = std::find(begin(m_sources), end(m_sources), *it);
				if (result != std::end(m_sources)) {
					m_sources.erase(result);
					m_removable.erase(it);
					//goto yes;
					break;
				}
			}
		}
	}
public:
	SFX() {
		m_sounds[Sound::Rotate].loadFromFile("audio/tetris rotation q.ogg");
		m_sounds[Sound::Move].loadFromFile("audio/tetris move.ogg");
		m_sounds[Sound::Lock].loadFromFile("audio/tetris lock.ogg");

		m_thread.launch();
	}
	void play(nora::Sound t_sound) {
		m_sources.emplace_back(m_nextID, m_sounds[t_sound], callback_f);
		m_nextID++;
	}
};
inline SFX sfx;

_NORA_END