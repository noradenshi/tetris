#include "Piece.h"

void PieceCell::rotate(bool right) {
	std::swap(m_offset.x, m_offset.y);
	m_offset.x *= (right) ? -1 : 1;
	m_offset.y *= (right) ? 1 : -1;
}

void Piece::getMaxMinOffset() {
	m_max_offset = { 0, 0 };
	m_min_offset = { 0, 0 };
	for (auto cell : m_piece) {
		m_max_offset.x = std::max(m_max_offset.x, cell.getOffset().x);
		m_max_offset.y = std::max(m_max_offset.y, cell.getOffset().y);
		m_min_offset.x = std::min(m_min_offset.x, cell.getOffset().x);
		m_min_offset.y = std::min(m_min_offset.y, cell.getOffset().y);
	}
}

void Piece::setType(PieceType piece) {
	m_type = piece;
	switch (piece) {
	case PieceType::o:
		m_pos = { 4, 0 };
		m_piece[0].setOffset(0, 0);
		m_piece[1].setOffset(0, 1);
		m_piece[2].setOffset(1, 0);
		m_piece[3].setOffset(1, 1);
		break;
	case PieceType::s:
		m_pos = { 4, 0 };
		m_piece[0].setOffset(0, 0);
		m_piece[1].setOffset(1, 0);
		m_piece[2].setOffset(0, 1);
		m_piece[3].setOffset(-1, 1);
		break;
	case PieceType::z:
		m_pos = { 5, 0 };
		m_piece[0].setOffset(0, 0);
		m_piece[1].setOffset(-1, 0);
		m_piece[2].setOffset(0, 1);
		m_piece[3].setOffset(1, 1);
		break;
	case PieceType::t:
		m_pos = { 4, 0 };
		m_piece[0].setOffset(0, 0);
		m_piece[1].setOffset(-1, 0);
		m_piece[2].setOffset(1, 0);
		m_piece[3].setOffset(0, 1);
		break;
	case PieceType::l:
		m_pos = { 5, 0 };
		m_piece[0].setOffset(0, 0);
		m_piece[1].setOffset(1, 0);
		m_piece[2].setOffset(-1, 0);
		m_piece[3].setOffset(-1, 1);
		break;
	case PieceType::j:
		m_pos = { 4, 0 };
		m_piece[0].setOffset(0, 0);
		m_piece[1].setOffset(-1, 0);
		m_piece[2].setOffset(1, 0);
		m_piece[3].setOffset(1, 1);
		break;
	case PieceType::i:
		m_pos = { 4, 0 };
		m_piece[0].setOffset(0, 0);
		m_piece[1].setOffset(-1, 0);
		m_piece[2].setOffset(2, 0);
		m_piece[3].setOffset(1, 0);
		break;
	}
	getMaxMinOffset();
}

void Piece::rotate(bool right) {
	if (m_type == PieceType::o) return;
	for (auto& cell : m_piece) {
		cell.rotate(right);
	}
	getMaxMinOffset();
}

void Piece::move(Direction direction) {
	switch (direction) {
	case Direction::left: m_pos.x -= 1; break;
	case Direction::right:m_pos.x += 1; break;
	case Direction::up: m_pos.y -= 1; break;
	case Direction::down: m_pos.y += 1; break;
	}
}

PiecePreview::PiecePreview() {
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4 * 4); // 4 blocks, 4 vertices each
}

void PiecePreview::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}

void PiecePreview::setTexture(sf::Texture& t_texture) {
	m_texture = t_texture;
	setFillColor(sf::Color(206, 106, 206));
}

void PiecePreview::setPreviewType(PieceType piece) {
	setType(piece);
	for (int i = 0; i < 4; i++) {
		sf::Vertex* quad = &m_vertices[i * 4];
		quad[0].position = sf::Vector2f(getOffset(i).x * m_blockSize, getOffset(i).y * m_blockSize);
		quad[1].position = sf::Vector2f((getOffset(i).x + 1) * m_blockSize, getOffset(i).y * m_blockSize);
		quad[2].position = sf::Vector2f((getOffset(i).x + 1) * m_blockSize, (getOffset(i).y + 1) * m_blockSize);
		quad[3].position = sf::Vector2f(getOffset(i).x * m_blockSize, (getOffset(i).y + 1) * m_blockSize);

		quad[0].texCoords = sf::Vector2f(0, 0);
		quad[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
		quad[2].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
		quad[3].texCoords = sf::Vector2f(0, m_texture.getSize().y);
	}
}

void PiecePreview::setFillColor(sf::Color t_color) {
	for (int i = 0; i < 16; i++) {
		m_vertices[i].color = t_color;
	}
}