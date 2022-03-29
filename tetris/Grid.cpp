#include "Grid.h"

void GridCell::setState(bool isOccupied) {
	m_isOccupied = isOccupied;
	m_box.setFillColor((m_isOccupied) ? sf::Color(226, 106, 226, 255) : sf::Color::White);
}

void Grid::clearLines() {
	int amount = 0;
	for (int y = 0; y < height; y++) {
		bool isClearable = true;
		for (auto &cell : m_grid[y]) 
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
		m_stats[Lines] += amount;
		switch (amount) { // tetris classic values
		case 1: m_stats[Score] += 40 * m_stats[Level]; break;
		case 2: m_stats[Score] += 100 * m_stats[Level]; break;
		case 3: m_stats[Score] += 300 * m_stats[Level]; break;
		case 4: m_stats[Score] += 1200 * m_stats[Level]; break;
		}
		m_stats[Level] = m_stats[Lines] / 10 + 1;
	}
}

void Grid::updateCells(bool clear) {
	const short x = m_piece.getPosition().x;
	const short y = m_piece.getPosition().y;

	for (int i = 0; i < 4; i++) {
		sf::Vector2i offset = m_piece.getOffset(i);
		if (y + offset.y < 0) continue;
		m_grid[y + offset.y][x + offset.x].setTexture((clear) ? &m_textures["cell_background"] : &m_textures["cell_piece"]);
		m_grid[y + offset.y][x + offset.x].setState(!clear);
	}
}

Grid::Grid() {
	srand(time(NULL));

	m_textures["cell_background"].loadFromFile("graphics/block3.png");
	m_textures["cell_piece"].loadFromFile("graphics/block2.png");

	m_sounds["rotate"].loadFromFile("audio/tetris rotation q.ogg");
	m_sounds["lock"].loadFromFile("audio/tetris lock.ogg");
	m_sounds["move"].loadFromFile("audio/tetris move.ogg");

	m_sfx.setVolume(20);

	m_preview.setTexture(m_textures["cell_piece"]);
	m_preview.setPosition(m_previewPosition);

	reset();
}

void Grid::reset() {

	m_bagDrawer = BagDrawer();
	for (auto& stat : m_stats) {
		stat.second.reset();
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			m_grid[y][x].setSize(cell_size);
			m_grid[y][x].setTexture(&m_textures["cell_background"]);
			m_grid[y][x].setPosition(sf::Vector2f(offset_x + x, offset_y + y));
			m_grid[y][x].setState(false);
		}
	}

	m_preview.setPreviewType(m_bagDrawer.nextPiece());
	nextPiece();
}

void Grid::update(sf::Time& t_deltaTime) {

	int activeDirections = m_isMoving[0] + m_isMoving[1] + m_isMoving[2];
	if (m_isMoving[0] | m_isMoving[1] | m_isMoving[2]) {
		if (m_DAS <= sf::milliseconds(0)) {
			for (int i = 0; i < 3; i++) {
				if (m_isMoving[i]) {
					if (activeDirections > 1 && i == 1 &&  m_isLockable) continue; // allow to slide while soft droping
					move(static_cast<Direction>(i));
				}
			}
			m_DAS = (m_wasMoving) ? m_DAS_delay : m_DAS_initial;
		}
		m_DAS -= t_deltaTime;
		m_wasMoving = true;
	}
	else {
		m_DAS = sf::milliseconds(0);
		m_wasMoving = false;
	}

	if (m_isLockable) {
		m_lockDelay -= t_deltaTime;

		if (m_lockDelay <= sf::milliseconds(0)) {
			m_isLockable = false;
			nextPiece();
		}
	}
	else {
		m_gravityTimer -= t_deltaTime.asMilliseconds() * m_stats[Level];

		if (m_gravityTimer <= 0.f) {
			move(Direction::Down);
			m_gravityTimer = m_gravity;
		}
	}

	m_stats[Debug] = m_lockDelay.asMilliseconds();
}

void Grid::updateActiveCells() {
	for (int i = 0; i < 4; i++) {
		sf::Vector2i pos = m_piece.getPosition() + m_piece.getOffset(i);
		m_activeCells[i] = pos;
	}
}

bool Grid::isGood() {
	bool isLockable = false;
	for (auto &cell : m_piece) {
		sf::Vector2i pos = m_piece.getPosition() + cell.getOffset();

		if (pos.x < 0 || pos.x > (int)width - 1 || pos.y > (int)height - 1) return false;
		if (pos.y < 0) continue; // allow out of bounds rotations

		bool isActive = false;
		for (auto &active_cell : m_activeCells) { if (pos == active_cell) isActive = true; }
		if (!isActive && m_grid[pos.y][pos.x].isOccupied()) return false;
	
		if (pos.y >= (int)height - 1 || m_grid[pos.y + 1][pos.x].isOccupied()) {
			isLockable = true;
		}
	}
	m_isLockable = isLockable;
	return true;
}

void Grid::rotate(bool right) {
	m_sfx.setBuffer(m_sounds["rotate"]);
	m_sfx.play();
	updateActiveCells();
	updateCells(true);
	m_piece.rotate(right);
	bool isWallkick = false;

	if (!isGood()) {
		for (int i = 0; i < 4; i++) { // check if any wall kicks are available (one try for each directiion)
			m_piece.move(static_cast<Direction>(i));
			if (!isGood()) {
				if (m_piece.getType() == PieceType::i) { // nested check for the longer side of 'i' piece
					m_piece.move(static_cast<Direction>(i));
					if (!isGood()) m_piece.move(!static_cast<Direction>(i));
					else {
						isWallkick = true;
						break;
					}
				}
				m_piece.move(!static_cast<Direction>(i));
			}
			else {
				isWallkick = true;
				break;
			}
		}
		if (!isWallkick) m_piece.rotate(!right);
	}
	updateCells(false);
}

void Grid::move(Direction direction) {
	m_sfx.setBuffer(m_sounds["move"]);
	m_sfx.play();
	updateActiveCells();
	updateCells(true);
	m_piece.move(direction);

	if (!isGood()) {
		m_piece.move(!direction);
		if (direction == Direction::Down) {
			updateCells(false);
			nextPiece();
		}
	}
	else { // point per soft drop performed
		if (direction == Direction::Down && m_gravityTimer > 0) {
			m_stats[Score] += 1;
		}
	}
	updateCells(false);
}

void Grid::updateInputs(Direction direction, bool state) {
	switch (direction) {
	case Direction::Left: m_isMoving[0] = state; break;
	case Direction::Down: m_isMoving[1] = state; break;
	case Direction::Right: m_isMoving[2] = state; break;
	}
}

void Grid::nextPiece() {
	m_sfx.setBuffer(m_sounds["lock"]);
	m_sfx.play();
	m_isLockable = false;
	m_lockDelay = m_lockDelayTime;
	clearLines();
	m_piece.setType(m_preview.getPreviewType());
	m_preview.setPreviewType(m_bagDrawer.nextPiece());
	updateCells(false);
}