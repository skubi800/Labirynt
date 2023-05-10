#pragma once

class Tile {
	unsigned int x;
	unsigned int y;

	unsigned int resolution;
	unsigned short borderSize;

	sf::RenderWindow& window;

	sf::RectangleShape tile;
	sf::RectangleShape border;

	sf::Color color;

public:
	bool visited; 
	bool borderLeft;
	bool borderRight;
	bool borderTop;
	bool borderBottom;

	Tile(sf::RenderWindow& window, unsigned int resolution, unsigned short borderSize, unsigned int x = 0, unsigned y = 0) 
		: window(window), resolution(resolution), borderSize(borderSize), x(x), y(y) {
		
		tile.setSize(sf::Vector2f(resolution, resolution));
		borderLeft = true;
		borderRight = true;
		borderTop = true;
		borderBottom = true;

		visited = false;

		color = sf::Color(169, 169, 169);
		tile.setFillColor(color);
	}

	void setX(unsigned int x) { this->x = x; }

	void setY(unsigned int y) { this->y = y; }

	void determineLocation() {
		tile.setPosition(x, y);
	}

	void setBorderSize(unsigned short borderSize) { this->borderSize = borderSize; }

	void drawTile() {
		if (!borderLeft) { drawLeftBorder(sf::Color(169, 169, 169)); }

		if (!borderRight) { drawRightBorder(sf::Color(169, 169, 169)); }

		if (!borderTop) { drawTopBorder(sf::Color(169, 169, 169)); }

		if (!borderBottom) { drawBottomBorder(sf::Color(169, 169, 169)); }

		window.draw(tile);
	}

	void drawBorders(sf::Color color = sf::Color(169, 169, 169)) {
		drawLeftBorder(color);
		drawRightBorder(color);
		drawTopBorder(color);
		drawBottomBorder(color);
	}


	void drawLeftBorder(sf::Color color = sf::Color::Black) {
		border.setSize(sf::Vector2f(borderSize, resolution));
		border.setPosition(x - borderSize, y);
		border.setFillColor(color);
		window.draw(border);
	}

	void drawRightBorder(sf::Color color = sf::Color::Black) {
		border.setSize(sf::Vector2f(borderSize, resolution));
		border.setPosition(x + resolution, y);
		border.setFillColor(color);
		window.draw(border);
	}

	void drawTopBorder(sf::Color color = sf::Color::Black) {
		border.setSize(sf::Vector2f(resolution, borderSize));
		border.setPosition(x, y - borderSize);
		border.setFillColor(color);
		window.draw(border);
	}

	void drawBottomBorder(sf::Color color = sf::Color::Black) {
		border.setSize(sf::Vector2f(resolution, borderSize));
		border.setPosition(x, y + resolution);
		border.setFillColor(color);
		window.draw(border);
	}

	void changeColor(sf::Color color = sf::Color(169, 169, 169)) {
		this->color = color;
		tile.setFillColor(color);
	}
};

class TileParams {

	Tile* tile;

public:
	bool visited;
	bool readed;

	TileParams(Tile* tile) : tile(tile) {
		visited = false;
		readed = false;
	}

};