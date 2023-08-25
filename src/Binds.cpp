#include "Binds.h"

_NORA_BEGIN

Binds::Binds() {
	m_binds = {
	   {sf::Keyboard::Left, Action::Move_Left},
	   {sf::Keyboard::Right, Action::Move_Right},
	   {sf::Keyboard::Z, Action::Rotate_Left},
	   {sf::Keyboard::X, Action::Rotate_Right},
	   {sf::Keyboard::Up, Action::Rotate_Right},
	   {sf::Keyboard::Down, Action::Soft_Drop},
	   {sf::Keyboard::R, Action::Reset},
	};
}

void Binds::setGrid(Grid& t_grid) {
	grid = &t_grid;
}

void Binds::keyUpdate(sf::Keyboard::Key key, bool state) {
	if (grid == NULL) return;

	if (m_binds.find(key) != m_binds.end()) {
		m_actions.at(m_binds[key])(state);
	}
}

_NORA_END