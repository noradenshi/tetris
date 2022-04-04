#pragma once
//#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>
#include <random>

enum class PieceType {
	o, s, z, t, l, j, i, all
};
enum class Direction {
	Left, Down, Right, Up
};
inline Direction operator ! (const Direction& rh) {
	return static_cast<Direction>(static_cast<int>(rh) ^ 0b10);
}

class Bag {
	std::vector<PieceType> m_queue;
	std::random_device rd;

	void generateBag() {
		for (int i = 0; i < static_cast<int>(PieceType::all); i++) {
			m_queue.push_back(static_cast<PieceType>(i));
		}
		std::shuffle(m_queue.begin(), m_queue.end(), rd);
	}
public:
	Bag() {
		generateBag();
	}
	PieceType nextPiece(){
		PieceType back = m_queue.back();
		m_queue.pop_back();
		if (m_queue.size() < 1)
			generateBag();
		return back;
	}

	void operator = (Bag &rh) {
		m_queue = rh.m_queue;
	}
};

class BagDrawer {
	const static int size = 2;
	std::array<Bag, size> m_bags;

public:
	PieceType nextPiece() {
		return m_bags[rand() % size].nextPiece();
	}

	void operator = (BagDrawer rh) {
		m_bags = rh.m_bags;
	}
};

class PieceCell {
	sf::Vector2i m_offset;

public:
	void setOffset(short x, short y) { m_offset.x = x; m_offset.y = y; }
	sf::Vector2i getOffset() { return m_offset; }
	void rotate(bool right);
};

class Piece {
protected:
	PieceType m_type;
	std::array<PieceCell, 4> m_piece;
	sf::Vector2i m_pos;
	sf::Vector2i m_max_offset, m_min_offset;

	void getMaxMinOffset();
public:
	void setType(PieceType piece);
	PieceType getType() { return m_type; }
	void rotate(bool right);
	void move(Direction direction);
	sf::Vector2i getPosition() { return m_pos; }
	sf::Vector2i getOffset(short id) { return m_piece[id].getOffset(); }

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
	void setTexture(sf::Texture* t_texture);
	void setPreviewType(PieceType piece);
	void setFillColor(sf::Color t_color);
	PieceType getPreviewType() { return getType(); }
	sf::Color getFillColor() { return m_vertices[0].color; }

	void operator = (PiecePreview rh) {
		setPreviewType(rh.getPreviewType());
		setFillColor(rh.getFillColor());
	}
};