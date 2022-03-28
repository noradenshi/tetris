#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include "StatCallback.h"

class StatText  : public sf::Drawable
{
	const int name_size = 25, value_size = 30;
	const float offset = 40.f;
	sf::Text m_name, m_value;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
public:
	std::function<void(int)> valueCallback = [&](int t_value) {
		m_value.setString(std::to_string(t_value));
		m_value.setOrigin(m_value.getGlobalBounds().width / 2 // TODO: center below name
			, m_value.getGlobalBounds().height - offset / 2);
	};
	StatText();
	StatText(sf::Font& font, std::string string);
	void setFont(sf::Font& t_font);
	void setName(std::string t_string);
	void setPosition(sf::Vector2f t_pos);
};


class StatsUI : public sf::Drawable {
	sf::Font font;
	std::map<decltype(stat_name_t), StatText> m_stats = {
		{Score, StatText(font, "Score")},
		{Lines, StatText(font, "Lines Cleared")},
		{Level, StatText(font, "Level")},
		{Debug, StatText(font, "Lock Delay")},
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
public:
	StatsUI();
	void subscribeTo(std::map<decltype(stat_name_t), StatValue>& t_stats);
};

