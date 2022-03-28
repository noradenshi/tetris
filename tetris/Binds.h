#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <functional>
#include "Grid.h"

enum class Action {
	None,
	Move_Left,
	Move_Right,
	Rotate_Left,
	Rotate_Right,
	Soft_Drop,
	Reset,
	Size,
};

class Binds
{
	Grid* grid;

	const std::map <Action, std::function<void(bool)>> m_actions = {
		{Action::None, [](bool) {}},

		{Action::Move_Left, [=](bool state) {
			grid->updateInputs(Direction::Left, state);
		}},

		{Action::Move_Right, [=](bool state) { 
			grid->updateInputs(Direction::Right, state);
		}},

		{Action::Rotate_Left, [=](bool state) { 
			if (state) {
				grid->rotate(false);
			}}},

		{Action::Rotate_Right, [=](bool state) { 
			if (state) {
				grid->rotate(true);
			}}},

		{Action::Soft_Drop, [=](bool state) { 
			grid->updateInputs(Direction::Down, state);
		}},

		{Action::Reset, [=](bool state) { 
			if (state) {
				grid->reset();
			}}},
	};

	std::map<sf::Keyboard::Key, Action> m_binds = {
		{sf::Keyboard::Left, Action::Move_Left},
		{sf::Keyboard::Right, Action::Move_Right},
		{sf::Keyboard::Z, Action::Rotate_Left},
		{sf::Keyboard::X, Action::Rotate_Right},
		{sf::Keyboard::Up, Action::Rotate_Right},
		{sf::Keyboard::Down, Action::Soft_Drop},
		{sf::Keyboard::R, Action::Reset},
	};


public:
	Binds(Grid &t_grid) {
		grid = &t_grid;
	}
	void keyUpdate(sf::Keyboard::Key key, bool state) {
		if (m_binds.find(key) != m_binds.end()) {
			m_actions.at(m_binds[key])(state);
		}
	}
};

