#pragma once
#include <vector>
#include <random>

class Labyrinth {

	Tile*** tiles;
	sf::RenderWindow& window;

	unsigned short borderSize;
	unsigned short resolution;
	unsigned int width;
	unsigned int height;

	bool isGenerated_;
	bool isGenerating_;

	sf::Vector2i currPos;
	sf::Texture texture;
	sf::Sprite shape;

	void deleteTiles(){
		if (!tiles)
			return;

		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				delete tiles[i][j];
			}
			delete[] tiles[i];
		}
		
		delete[] tiles;
	}

public:
	Labyrinth(sf::RenderWindow& window, unsigned int width, unsigned int height, unsigned int resolution, unsigned short borderSize)
		: window(window), width(width), height(height), resolution(resolution), borderSize(borderSize) {
		tiles = nullptr;
		isGenerated_ = false;
		isGenerating_ = false;
		currPos = { 0,0 };
		generateTilesLocations();
	}

	~Labyrinth() { deleteTiles(); }

	void generateTilesLocations() {
		if (tiles)
			deleteTiles();

		tiles = new Tile ** [height];
		std::thread t1, t2;

		
		t1 = std::thread([this]() {
			for (unsigned int i = 0; i < this->height/2; i++) {
				this->tiles[i] = new Tile * [this->width];

				for (unsigned int j = 0; j < this->width; j++) {
					this->tiles[i][j] = new Tile(window, resolution, borderSize);

					this->tiles[i][j]->setX(this->borderSize * (i + 1) + i * this->resolution);
					this->tiles[i][j]->setY(this->borderSize * (j + 1) + j * this->resolution);
					this->tiles[i][j]->determineLocation();
				}
			}
			});

		t2 = std::thread([this]() {
			for (unsigned int i = height / 2; i < height; i++) {
				this->tiles[i] = new Tile * [width];

				for (unsigned int j = 0; j < width; j++) {
					this->tiles[i][j] = new Tile(window, resolution, borderSize);

					this->tiles[i][j]->setX(borderSize * (i + 1) + i * resolution);
					this->tiles[i][j]->setY(borderSize * (j + 1) + j * resolution);
					this->tiles[i][j]->determineLocation();
				}
			}
			});


		t1.join();
		t2.join();
	}

	void draw() {
		if (!tiles)
			return;

		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				tiles[i][j]->drawTile();
			}
		}

		texture.create(window.getSize().x, window.getSize().y);
		texture.update(window);
		shape.setTexture(texture);
	}

	void textureDraw() {
		window.draw(shape);
	}

	void changeColor(sf::Vector2i pos) {
		int x = pos.x;
		int y = pos.y;
		x = (x - resolution / 2) / (resolution + borderSize);
		y = (y - resolution / 2) / (resolution + borderSize);

		if (x >= 0 && y >= 0)
			tiles[x][y]->changeColor(sf::Color(80, 228, 0));
	}

	void getVisitedNeighbors(std::vector<sf::Vector2i>& positions, sf::Vector2i position) {
		if (position.x < 0 || position.y < 0)
			return;

		if (position.x + 1 < height) {
			if (tiles[position.x + 1][position.y]->visited) {
				positions.push_back({ position.x + 1, position.y });
			}
		}

		if (position.x - 1 >= 0) {
			if (tiles[position.x - 1][position.y]->visited)
				positions.push_back({ position.x - 1, position.y });
		}

		if (position.y + 1 < width) {
			if (tiles[position.x][position.y + 1]->visited)
				positions.push_back({ position.x, position.y + 1 });
		}

		if (position.y - 1 >= 0) {
			if (tiles[position.x][position.y - 1]->visited)
				positions.push_back({ position.x, position.y - 1 });
		}
	}
	
	void getUnVisitedNeighbors(std::vector<sf::Vector2i>& positions, sf::Vector2i position) {
		if (position.x < 0 || position.y < 0)
			return;

		if (position.x + 1 < height) {
			if (!tiles[position.x + 1][position.y]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x + 1, position.y)) == positions.end()) {
					positions.push_back({ position.x + 1, position.y });
					tiles[position.x + 1][position.y]->changeColor(sf::Color::Red);
					tiles[position.x + 1][position.y]->drawTile();
				}
			}
		}

		if (position.x - 1 >= 0) {
			if (!tiles[position.x - 1][position.y]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x - 1, position.y)) == positions.end()) {
					positions.push_back({ position.x - 1, position.y });
					tiles[position.x - 1][position.y]->changeColor(sf::Color::Red);
					tiles[position.x - 1][position.y]->drawTile();
				}
			}
		}

		if (position.y + 1 < width) {
			if (!tiles[position.x][position.y + 1]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x, position.y + 1)) == positions.end()) {
					positions.push_back({ position.x, position.y + 1 });
					tiles[position.x][position.y + 1]->changeColor(sf::Color::Red);
					tiles[position.x][position.y + 1]->drawTile();
				}
			}
		}

		if (position.y - 1 >= 0) {
			if (!tiles[position.x][position.y - 1]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x, position.y - 1)) == positions.end()) {
					positions.push_back({ position.x, position.y - 1 });
					tiles[position.x][position.y - 1]->changeColor(sf::Color::Red);
					tiles[position.x][position.y - 1]->drawTile();
				}
			}
		}
	}

	void primsAlgorithm() {
		isGenerating_ = true;
		window.setActive(true);
		std::vector<sf::Vector2i> neighbors;
		std::vector<sf::Vector2i> visited;
		sf::Vector2i pos = { 0,0 };
		sf::Vector2i nextPos;
		unsigned int posVector;
		std::vector<sf::Vector2i>::iterator temp;

		getUnVisitedNeighbors(neighbors, pos);
		tiles[pos.x][pos.x]->visited = true;

		srand(time(NULL));

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist;


		while (neighbors.size()) {
			//posVector = rand() % neighbors.size();
			posVector = dist(rng) % neighbors.size();
			nextPos = neighbors[posVector];

			neighbors.erase(neighbors.begin() + posVector);

			window.clear();
			textureDraw();
			getUnVisitedNeighbors(neighbors, nextPos);

			tiles[nextPos.x][nextPos.y]->visited = true;
			tiles[nextPos.x][nextPos.y]->changeColor();
			tiles[nextPos.x][nextPos.y]->drawTile();

			visited.clear();
			getVisitedNeighbors(visited, nextPos);

			pos = visited[rand() % visited.size()];

		
			if (pos.x < nextPos.x) {
				tiles[nextPos.x][nextPos.y]->borderLeft = false;
				tiles[nextPos.x][nextPos.y]->drawLeftBorder();

				if (nextPos.x - 1 >= 0 )
					tiles[nextPos.x - 1][nextPos.y]->borderRight = false;
			}
			else if (pos.x > nextPos.x) {
				tiles[nextPos.x][nextPos.y]->borderRight = false;
				tiles[nextPos.x][nextPos.y]->drawRightBorder();

				if (nextPos.x + 1 < width)
					tiles[nextPos.x + 1][nextPos.y]->borderLeft = false;
			}
			else if (pos.y < nextPos.y) {
				tiles[nextPos.x][nextPos.y]->borderTop = false;
				tiles[nextPos.x][nextPos.y]->drawTopBorder();

				if (nextPos.y - 1 >= 0)
					tiles[nextPos.x][nextPos.y - 1]->borderBottom = false;
			}
			else if (pos.y > nextPos.y) {
				tiles[nextPos.x][nextPos.y]->borderBottom = false;
				tiles[nextPos.x][nextPos.y]->drawBottomBorder();

				if (nextPos.y + 1 < height) 
					tiles[nextPos.x][nextPos.y + 1]->borderTop = false;
			}

			texture.update(window);
			
			window.display();
		}
		
		isGenerated_ = true;
		textureDraw();
		window.display();

		window.setActive(false);
	}
	
	bool isGenerated() { return isGenerated_; }

	bool isGenerating() { return isGenerating_; }

	void movePlayer(sf::Keyboard::Key key) {

		if (key == sf::Keyboard::Right) {
			if (!tiles[currPos.x][currPos.y]->borderRight) {
				textureDraw();
			
				currPos.x += 1;

				tiles[currPos.x][currPos.y]->changeColor(sf::Color::Green);
				tiles[currPos.x][currPos.y]->drawTile();
				window.display();
			}
		}
		else if (key == sf::Keyboard::Left) {
			if (!tiles[currPos.x][currPos.y]->borderLeft) {
				textureDraw();
				currPos.x -= 1;

				tiles[currPos.x][currPos.y]->changeColor(sf::Color::Green);
				tiles[currPos.x][currPos.y]->drawTile();
				window.display();
			}
		}
		else if (key == sf::Keyboard::Down) {
			if (!tiles[currPos.x][currPos.y]->borderBottom) {
				textureDraw();
				currPos.y += 1;

				tiles[currPos.x][currPos.y]->changeColor(sf::Color::Green);
				tiles[currPos.x][currPos.y]->drawTile();
				window.display();
			}
		}
		else if (key == sf::Keyboard::Up) {
			if (!tiles[currPos.x][currPos.y]->borderTop) {
				textureDraw();
				currPos.y -= 1;

				tiles[currPos.x][currPos.y]->changeColor(sf::Color::Green);
				tiles[currPos.x][currPos.y]->drawTile();
				window.display();
			}
		}

	//	draw();


		if (currPos.x == width - 1 && currPos.y == height - 1) {
			sf::Font font;

			if (font.loadFromFile("font.otf")) {
				sf::Text text;
				text.setFont(font);
				text.setCharacterSize(15);
				text.setString("Udalo sie ukonczyc labirynt");
				//text.setStyle(sf::Text::Bold);
				text.setPosition(5, 0);
				text.setFillColor(sf::Color::Red);
				window.draw(text);
				window.display();
			}
		}

		
	}
};