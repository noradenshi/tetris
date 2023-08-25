#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include "StatCallback.h"
#include "common.h"

_NORA_BEGIN

class StatText : public sf::Drawable
{
	const int name_size = 35, value_size = 40;
	const float offset = 40.f;
	sf::Text m_name, m_value;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
public:
	callback_t valueCallback = [&m_value = m_value, &offset = offset](int t_value) {
		m_value.setString(std::to_string(t_value));
		m_value.setOrigin(m_value.getGlobalBounds().width / 2 // TODO: center below name
			, m_value.getGlobalBounds().height - offset / 2);
	};

	StatText(sf::Font& font, std::string string);
	void setFont(sf::Font& t_font);
	void setName(std::string t_string);
	void setPosition(sf::Vector2f t_pos);
};

class StatsUI : public sf::Drawable {
	sf::Font font;
	std::map<stat_name_t, StatText*> m_stats = {
		{Score, new StatText(font, "Score")},
		{Lines, new StatText(font, "Lines")},
		{Level, new StatText(font, "Level")},
		{Debug, new StatText(font, "Lock Delay")},
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
public:
	StatsUI();
	void subscribeTo(std::map<stat_name_t, StatValue>& t_stats);
};

_NORA_END