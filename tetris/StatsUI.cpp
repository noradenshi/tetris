#include "StatsUI.h"

void StatText::draw(sf::RenderTarget& target, sf::RenderStates) const {
	target.draw(m_name);
	target.draw(m_value);
}

StatText::StatText(sf::Font& t_font, std::string t_string) {
	m_name.setCharacterSize(name_size);
	m_value.setCharacterSize(value_size);
	m_name.setFillColor(sf::Color::White);

	setFont(t_font);
	setName(t_string);
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
	m_name.setOrigin(m_name.getGlobalBounds().width, m_name.getGlobalBounds().height + offset / 2);
}

void StatsUI::draw(sf::RenderTarget& target, sf::RenderStates) const {
	for (auto& stat : m_stats)
		target.draw(*stat.second);
}

StatsUI::StatsUI() {
	font.loadFromFile("AlloyInk.otf");
	for (int i = 0; i < m_stats.size(); i++)
		m_stats[static_cast<stat_name_t>(i)]->setPosition(sf::Vector2f(280, 150 + 100 * i));
}

void StatsUI::subscribeTo(std::map<stat_name_t, StatValue>& t_stats) {
	for (auto& stat : m_stats)
		t_stats[stat.first].setCallback(stat.second->valueCallback);
}