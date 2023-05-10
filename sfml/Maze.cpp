#include "Maze.h"

// PRIVATE SECTION
void SquareMaze::deleteTiles() {
	if (!this->tiles)
		return;

	for (unsigned short i = 0; i < this->width; i++) {
		for (unsigned short j = 0; j < this->height; j++) {
			delete this->tiles[i][j];
		}
		delete[] this->tiles[i];
	}

	delete[] this->tiles;
	this->tiles = nullptr;
}
void SquareMaze::generateTiles() {
	if (this->tiles) deleteTiles();

	this->tiles = new SquareTile * *[this->width];

	for (unsigned short i = 0; i < this->width; i++) {
		this->tiles[i] = new SquareTile * [this->height];

		for (unsigned short j = 0; j < this->height; j++) {
			this->tiles[i][j] = new SquareTile();

			this->tiles[i][j]->x = this->borderSize * (i + 1) + i * this->resolution;
			this->tiles[i][j]->y = this->borderSize * (j + 1) + j * this->resolution;
		}
	}
}
void SquareMaze::generateTexture() {
	if (!this->tiles) return;

	float width = this->width * this->resolution + (this->width + 1) * this->borderSize;
	float height = this->height * this->resolution + (this->height + 1) * this->borderSize;
	Drawable::createTexture({ width,height });

	sf::RectangleShape tile;
	tile.setSize({ this->resolution, this->resolution });
	tile.setFillColor(this->colorOfTiles);

	for (unsigned short i = 0; i < this->width; i++) {
		for (unsigned short j = 0; j < this->height; j++) {
			tile.setPosition(this->tiles[i][j]->x, this->tiles[i][j]->y);
			Drawable::draw(&tile);
		}
	}
}

void SquareMaze::changeColorOfTile(sf::Vector2i pos, sf::Color color) {
	sf::RectangleShape tile;
	tile.setSize({ this->resolution, this->resolution });
	tile.setPosition(this->tiles[pos.x][pos.y]->x, this->tiles[pos.x][pos.y]->y);
	tile.setFillColor(color);
	Drawable::draw(&tile);
}
void SquareMaze::drawLeftBorder(sf::Vector2i& pos) {
	this->border.setSize(sf::Vector2f(this->borderSize, this->resolution));
	this->border.setPosition(this->tiles[pos.x][pos.y]->x - this->borderSize, this->tiles[pos.x][pos.y]->y);
	Drawable::draw(&this->border);
}
void SquareMaze::drawRightBorder(sf::Vector2i& pos) {
	this->border.setSize(sf::Vector2f(this->borderSize, this->resolution));
	this->border.setPosition(this->tiles[pos.x][pos.y]->x + this->resolution, this->tiles[pos.x][pos.y]->y);
	Drawable::draw(&this->border);
}
void SquareMaze::drawTopBorder(sf::Vector2i& pos) {
	this->border.setSize(sf::Vector2f(this->resolution, this->borderSize));
	this->border.setPosition(this->tiles[pos.x][pos.y]->x, this->tiles[pos.x][pos.y]->y - this->borderSize);
	Drawable::draw(&this->border);
}
void SquareMaze::drawBottomBorder(sf::Vector2i& pos) {
	this->border.setSize(sf::Vector2f(this->resolution, this->borderSize));
	this->border.setPosition(this->tiles[pos.x][pos.y]->x, this->tiles[pos.x][pos.y]->y + this->resolution);
	Drawable::draw(&this->border);
}


// CONSTRUCTOR & DECONSTRUCTOR
SquareMaze::SquareMaze(unsigned short width, unsigned short height, float resolution, float borderSize, sf::Color color)
	: width(width), height(height), borderSize(borderSize), resolution(resolution), colorOfTiles(color) {
	this->tiles = nullptr;
	generateTiles();
	generateTexture();

	this->border.setFillColor(color);
}
SquareMaze::~SquareMaze() { 
	deleteTiles();
}


// PUBLIC SECTION
void SquareMaze::refresh() {
	generateTiles();
	generateTexture();
}