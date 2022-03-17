#pragma once
//#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

enum class PieceType {
	o, s, z, t, l, j, i, all
};
enum class Direction {
	left, up, right, down
};
inline Direction operator ! (const Direction& rh) {
	return static_cast<Direction>(static_cast<int>(rh) ^ 0b10);
}

class PieceCell {
	sf::Vector2s m_offset;

public:
	void setOffset(short x, short y) { m_offset.x = x; m_offset.y = y; }
	sf::Vector2s getOffset() { return m_offset; }
	void rotate(bool right);
};


class Piece {
	PieceType m_type;
	std::array<PieceCell, 4> m_piece;
	sf::Vector2i m_cur_pos;
	sf::Vector2s m_max_offset, m_min_offset;

	void getMaxMinOffset();
public:
	void setType(PieceType piece);
	PieceType getType() { return m_type; }
	void rotate(bool right);
	void move(Direction direction);
	sf::Vector2i getPosition() { return m_cur_pos; }
	sf::Vector2s getOffset(short id) { return m_piece[id].getOffset(); }

	std::_Array_iterator<PieceCell, 4> begin() { return m_piece.begin(); }
	std::_Array_iterator<PieceCell, 4> end() { return m_piece.end(); }
};

class PiecePreview : private Piece, public sf::Drawable, public sf::Transformable {
	const int m_blockSize = 30;
	sf::VertexArray m_vertices;
	sf::Texture m_texture;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	PiecePreview();
	void setTexture(sf::Texture& t_texture);
	void setPreviewType(PieceType piece);
	void setFillColor(sf::Color t_color);
	PieceType getPreviewType() { return getType(); }
};