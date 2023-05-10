#pragma once
#include "Common.h"
#include "Drawable.h"

class SquareMazeSolver;

class SquareTile {

	unsigned short x;
	unsigned short y;

	bool visited;

	bool borderLeft;
	bool borderRight;
	bool borderTop;
	bool borderBottom;
public:
	
	SquareTile(unsigned short x = 0, unsigned short y = 0) : x(x), y(y) {
		this->visited = false;

		this->borderLeft = true;
		this->borderRight = true;
		this->borderTop = true;
		this->borderBottom = true;
	}

	friend class SquareMaze;
	friend class SquareMazeSolver;
	friend class Prims;
};

class SquareMaze : public Drawable{
	SquareTile*** tiles;

	float borderSize;
	float resolution;

	unsigned short width;
	unsigned short height;

	sf::Color colorOfTiles;

	sf::RectangleShape border;

	void deleteTiles();
	void generateTiles();
	void generateTexture();

	void changeColorOfTile(sf::Vector2i pos, sf::Color color = sf::Color(0,191,255));
	void drawLeftBorder(sf::Vector2i& pos);
	void drawRightBorder(sf::Vector2i& pos);
	void drawTopBorder(sf::Vector2i& pos);
	void drawBottomBorder(sf::Vector2i& pos);

public:
	SquareMaze(unsigned short width, unsigned short height, float resolution, float borderSize, sf::Color color);
	virtual ~SquareMaze();

	void refresh();
	
	friend class SquareMazeSolver;
	friend class Prims;
};