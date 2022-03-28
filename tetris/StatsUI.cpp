#include "StatsUI.h"

void StatText::draw(sf::RenderTarget& target, sf::RenderStates) const {
	target.draw(m_name);
	target.draw(m_value);
}

StatText::StatText() {
	m_name.setCharacterSize(name_size);
	m_value.setCharacterSize(value_size);
	m_name.setFillColor(sf::Color::White);
}

void StatText::setFont(sf::Font& t_font) {
	m_name.setFont(t_font);
	m_value.setFont(t_font);
}

void StatText::setName(std::string t_string) {
	m_name.setString(t_string);
	m_name.setOrigin(m_name.getGlobalBounds().width, m_name.getGlobalBounds().height + offset / 2);
}

void StatText::setPosition(sf::Vector2f t_pos) {
	m_name.setPosition(t_pos);
	m_value.setPosition(t_pos);
}

void StatsUI::draw(sf::RenderTarget& target, sf::RenderStates) const {
	target.draw(m_score);
	target.draw(m_linesCleared);
	target.draw(m_level);
	target.draw(m_debug);
}

StatsUI::StatsUI() {
	font.loadFromFile("AlloyInk.otf");
	m_score.setFont(font);
	m_linesCleared.setFont(font);
	m_level.setFont(font);
	m_debug.setFont(font);
	m_score.setName("score");
	m_linesCleared.setName("lines");
	m_level.setName("level");
	m_debug.setName("lock delay");
	m_score.setPosition(sf::Vector2f(200, 100));
	m_linesCleared.setPosition(sf::Vector2f(200, 200));
	m_level.setPosition(sf::Vector2f(200, 300));
	m_debug.setPosition(sf::Vector2f(200, 400));
}

void StatsUI::subscribeTo(std::map<decltype(stat_name_t), StatValue>& t_stats) {
	t_stats[Score].setCallback(m_score.valueCallback);
	t_stats[Lines].setCallback(m_linesCleared.valueCallback);
	t_stats[Level].setCallback(m_level.valueCallback);
	t_stats[Debug].setCallback(m_debug.valueCallback);
}