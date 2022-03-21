#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <array>
#include "Stat.h"

class StatText  : public sf::Drawable
{
	const int name_size = 25, value_size = 30;
	const float offset = 40.f;
	sf::Text m_name, m_value;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const {
		target.draw(m_name);
		target.draw(m_value);
	}
public:
	std::function<void(int)> valueCallback = [&](int t_value) {
		m_value.setString(std::to_string(t_value));
		m_value.setOrigin(m_value.getGlobalBounds().width * 0, m_value.getGlobalBounds().height - offset / 2);
	};
	StatText() { 
		m_name.setCharacterSize(name_size);
		m_value.setCharacterSize(value_size);
		m_name.setFillColor(sf::Color::White);
	}
	void setFont(sf::Font& t_font) {
		m_name.setFont(t_font);
		m_value.setFont(t_font);
	}
	void setName(std::string t_string) {
		m_name.setString(t_string);
		m_name.setOrigin(m_name.getGlobalBounds().width * 0, m_name.getGlobalBounds().height + offset / 2);
	}
	void setPosition(sf::Vector2f t_pos) {
		m_name.setPosition(t_pos);
		m_value.setPosition(t_pos);
	}
};


class StatsUI : public sf::Drawable {
	sf::Font font;
	StatText m_score, m_linesCleared, m_level;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const {
		target.draw(m_score);
		target.draw(m_linesCleared);
		target.draw(m_level);
	}
public:
	StatsUI() {
		font.loadFromFile("AlloyInk.otf");
		m_score.setFont(font);
		m_linesCleared.setFont(font);
		m_level.setFont(font);
		m_score.setName("score");
		m_linesCleared.setName("lines");
		m_level.setName("level");
		m_score.setPosition(sf::Vector2f(150, 100));
		m_linesCleared.setPosition(sf::Vector2f(150, 300));
		m_level.setPosition(sf::Vector2f(150, 500));
	}
	void subscribeTo(std::array<Stat, 3> t_stats) {
		t_stats[0].setCallback(m_score.valueCallback);
		t_stats[1].setCallback(m_linesCleared.valueCallback);
		t_stats[2].setCallback(m_level.valueCallback);
	}
	void subscribeToScore(Stat& stat) {
		stat.setCallback(m_score.valueCallback);
	}
	void subscribeToLines(Stat& stat) {
		stat.setCallback(m_linesCleared.valueCallback);
	}
	void subscribeToLevel(Stat& stat) {
		stat.setCallback(m_level.valueCallback);
	}
};

