#include "Grid.h"

void GridCell::setState(bool isOccupied) {
	m_isOccupied = isOccupied;
	m_box.setFillColor((m_isOccupied) ? sf::Color(226, 106, 226, 255) : sf::Color::White);
}

#include <iostream>
void Grid::clearLines() {
	int amount = 0;
	for (int y = 0; y < height; y++) {
		bool isClearable = true;
		for (auto cell : m_grid[y]) 
			if (!cell.isOccupied()) isClearable = false;
		
		if (isClearable) {
			amount++;
			for (int i = y; i > 0; i--) {
				std::swap(m_grid[i], m_grid[i - 1]);
				for (int j = 0; j < width; j++) {
					m_grid[i][j].setPosition(sf::Vector2f(offset_x + j, offset_y + i));
				}
			}
			for (int j = 0; j < width; j++) {
				m_grid[0][j] = GridCell();
				m_grid[0][j].setSize(cell_size);
				m_grid[0][j].setTexture(&m_textures["cell_background"]);
				m_grid[0][j].setPosition(sf::Vector2f(offset_x + j, offset_y));
			}
		}
	}
	if (amount > 0) {
		std::cout << "cleared " << amount << " lines!\n";
		if (amount == 4) std::cout << "!!! TETRIS !!!\n";

		m_linesCleared += amount;
		switch (amount) { // tetris classic values
		case 1: m_score += 40 * m_level; break;
		case 2: m_score += 100 * m_level; break;
		case 3: m_score += 300 * m_level; break;
		case 4: m_score += 1200 * m_level; break;
		}
		m_level = m_linesCleared / 10 + 1; 
		std::cout << "score: " << m_score << std::endl;
		std::cout << "lines cleared: " << m_linesCleared << std::endl;
		std::cout << "level: " << m_level << std::endl;
	}
}

void Grid::updateCells(bool clear) {
	for (int i = 0; i < 4; i++) {
		const short x = m_piece.getPosition().x;
		const short y = m_piece.getPosition().y;
		sf::Vector2s offset = m_piece.getOffset(i);
		m_grid[y + offset.y][x + offset.x].setTexture((clear) ? &m_textures["cell_background"] : &m_textures["cell_piece"]);
		m_grid[y + offset.y][x + offset.x].setState(!clear);
	}
}

Grid::Grid() {
	srand(time(NULL));

	m_textures["cell_background"].loadFromFile("block3.png");
	m_textures["cell_piece"].loadFromFile("block2.png");

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			m_grid[y][x].setSize(cell_size);
			m_grid[y][x].setTexture(&m_textures["cell_background"]);
			m_grid[y][x].setPosition(sf::Vector2f(offset_x + x, offset_y + y));
		}
	}

	m_preview.setTexture(m_textures["cell_piece"]);
	m_preview.setPosition(m_previewPosition);
	nextPiece();
	updateCells(false);
}

void Grid::update(sf::Time& t_deltaTime) {
	m_gravityTimer -= t_deltaTime.asMilliseconds() * m_level;
	if (m_gravityTimer <= 0.f) {
		move(Direction::down);
		m_gravityTimer = m_gravity;
	}
	m_lockDelay -= t_deltaTime;
}

void Grid::updateActiveCells() {
	for (int i = 0; i < 4; i++) {
		sf::Vector2i pos = m_piece.getPosition() + sf::Vector2i(m_piece.getOffset(i).x, m_piece.getOffset(i).y);
		m_activeCells[i] = pos;
	}
}

bool Grid::isGood() {
	for (auto cell : m_piece) {
		sf::Vector2i pos = m_piece.getPosition() + sf::Vector2i(cell.getOffset().x, cell.getOffset().y);

		if (pos.x < 0 || pos.y < 0 || pos.x > width - 1 || pos.y > height - 1) return false;

		bool isActive = false;
		for (auto active_cell : m_activeCells) { if (pos == active_cell) isActive = true; }
		if (!isActive && m_grid[pos.y][pos.x].isOccupied()) return false;
	}
	return true;
}

void Grid::rotate(bool right) {
	updateActiveCells();
	updateCells(true);
	m_piece.rotate(right);
	m_isLockable = false;

	if (!isGood()) m_piece.rotate(!right);
	updateCells(false);
}

void Grid::move(Direction direction) {
	updateActiveCells();
	updateCells(true);
	m_piece.move(direction);
	m_isLockable = false;

	if (!isGood()) {
		m_piece.move(!direction);
		if (direction == Direction::down) {
			m_isLockable = true;
			if (m_lockDelay <= sf::milliseconds(0)) {
				updateCells(false);
				nextPiece();
			}
		}
	}
	updateCells(false);
}

void Grid::nextPiece() {
	m_lockDelay = m_lockDelayTime;
	clearLines();
	m_piece.setType(m_preview.getPreviewType());
	int piece_id = std::rand() % static_cast<int>(PieceType::all);
	m_preview.setPreviewType(static_cast<PieceType>(piece_id));
	updateCells(false);
}