#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <functional>
#include "Grid.h"
#include "common.h"

_NORA_BEGIN

enum class Action {
	None,
	Move_Left,
	Move_Right,
	Rotate_Left,
	Rotate_Right,
	Soft_Drop,
	Reset,
};

class Binds
{
	Grid* grid;

	const std::map <Action, std::function<void(bool)>> m_actions = {
		{Action::None, [](bool) {}},
		{Action::Move_Left, [=](bool state) { grid->updateInputs(Direction::Left, state); }},
		{Action::Move_Right, [=](bool state) { grid->updateInputs(Direction::Right, state); }},
		{Action::Rotate_Left, [=](bool state) { grid->updateInputs(Direction::Left, state, true); }},
		{Action::Rotate_Right, [=](bool state) { grid->updateInputs(Direction::Right, state, true); }},
		{Action::Soft_Drop, [=](bool state) { grid->updateInputs(Direction::Down, state); }},
		{Action::Reset, [=](bool state) { if (state) { grid->reset(); }}},
	};

	std::map<sf::Keyboard::Key, Action> m_binds;

public:
	Binds();
	void setGrid(Grid& t_grid);
	void keyUpdate(sf::Keyboard::Key key, bool state);
};
inline Binds binds;

_NORA_END