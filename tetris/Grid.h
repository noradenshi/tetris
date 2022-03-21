#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Piece.h"
#include "Stat.h"

class GridCell : public sf::Drawable {
	sf::RectangleShape m_box;
	float m_size = 0.f;
	bool m_isOccupied = false;

	void draw(sf::RenderTarget& target, sf::RenderStates) const {
		target.draw(m_box);
	}
public:
	GridCell() { m_box.setFillColor(sf::Color::White); }
	void setSize(const float cell_size) { m_size = cell_size; m_box.setSize(sf::Vector2f(m_size, m_size)); }
	void setTexture(sf::Texture* t_texture) { m_box.setTexture(t_texture); }
	void setPosition(sf::Vector2f t_pos) { m_box.setPosition(t_pos * m_size); }
	void setState(bool isOccupied);
	bool isOccupied() { return m_isOccupied; }
};

class Grid : public sf::Drawable {
	const float cell_size = 30.f;
	const static std::size_t height = 20;
	const static std::size_t width = 10;
	const static unsigned short offset_x = 15;
	const static unsigned short offset_y = 2;
	std::array<std::array<GridCell, width>, height> m_grid;
	std::array<sf::Vector2i, 4> m_activeCells;
	std::map<std::string, sf::Texture> m_textures;
	
	const sf::Vector2f m_previewPosition = { 850, 300 };
	Piece m_piece;
	PiecePreview m_preview;

	const float m_gravity = 1000;
	float m_gravityTimer = m_gravity * 2; // entry delay
	const sf::Time m_lockDelayTime = sf::milliseconds(100);
	sf::Time m_lockDelay;
	bool m_isLockable = false;

	Stat m_score;
	Stat m_linesCleared;
	Stat m_level = 1;

	void draw(sf::RenderTarget& target, sf::RenderStates) const {
		target.draw(m_preview);
		for (auto line : m_grid) for (auto cell : line) target.draw(cell);
	}
	void updateCells(bool clear);
	void clearLines();
	void updateActiveCells();
	bool isGood();
public:
	Grid();
	void update(sf::Time& deltaTime);
	void rotate(bool right);
	void move(Direction direction);
	void nextPiece();
	std::array<Stat, 3> getStats() {
		return std::array<Stat, 3>{m_score, m_linesCleared, m_level};
	}
	Stat& getScore() {
		return m_score;
	}
	Stat& getLines() {
		return m_linesCleared;
	}
	Stat& getLevel() {
		return m_level;
	}
};