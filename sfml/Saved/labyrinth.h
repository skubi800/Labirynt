#pragma once
#include <vector>

class Labyrinth {

	Tile*** tiles;
	sf::RenderWindow& window;

	unsigned short borderSize;
	unsigned short resolution;
	unsigned int width;
	unsigned int height;

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
		generateTilesLocations();
	}

	~Labyrinth() { deleteTiles(); }

	void generateTilesLocations() {
		if (tiles)
			deleteTiles();

		tiles = new Tile ** [height];

		for (unsigned int i = 0; i < height; i++) {
			tiles[i] = new Tile*[width];
			
			for (unsigned int j = 0; j < width; j++) {
				tiles[i][j] = new Tile(window, resolution, borderSize);

				tiles[i][j]->setX(borderSize * (i + 1) + i * resolution);
				tiles[i][j]->setY(borderSize * (j + 1) + j * resolution);
				tiles[i][j]->determineLocation();
				//tiles[i][j]->drawTile();
			}
		}
	}

	void draw() {
		if (!tiles)
			return;

		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				tiles[i][j]->drawTile();
			}
		}
	}

	void changeColor(sf::Vector2i pos) {
		int x = pos.x;
		int y = pos.y;
		x = (x - resolution / 2) / (resolution + borderSize);
		y = (y - resolution / 2) / (resolution + borderSize);

		if (x >= 0 && y >= 0)
			tiles[x][y]->changeColor(sf::Color(80, 228, 0));
	}

	/*
	void getNeighbors(std::vector<sf::Vector2i>& positions, sf::Vector2i position) {
		if (position.x < 0 || position.y < 0)
			return;

		if (position.x + 1 < width) {
			if (!tiles[position.x + 1][position.y]->visited)
				positions.push_back({ position.x + 1, position.y });
		}

		if (position.x - 1 >= 0) {
			if (!tiles[position.x - 1][position.y]->visited)
				positions.push_back({ position.x - 1, position.y });
		}

		if (position.y + 1 < height) {
			if (!tiles[position.x][position.y + 1]->visited)
				positions.push_back({ position.x, position.y + 1 });
		}

		if (position.y - 1 >= 0) {
			if (!tiles[position.x][position.y - 1]->visited)
				positions.push_back({ position.x, position.y - 1 });
		}
	}

	void primsAlgorithm() {
		std::vector<sf::Vector2i> neighbors;
		std::vector<sf::Vector2i> visited;
		sf::Vector2i pos = { 0,0 };
		sf::Vector2i nextPos;
		unsigned int posVector;

		getNeighbors(neighbors, pos);
		tiles[pos.x][pos.x]->visited = true;

		srand(time(NULL));


		while (neighbors.size()) {
			posVector = rand() % neighbors.size();
			nextPos = neighbors[posVector];

			neighbors.erase(neighbors.begin() + posVector);

			getNeighbors(neighbors, nextPos);

		//	tiles[nextPos.x][nextPos.y]->changeColor(sf::Color(80, 228, 0));
			tiles[nextPos.x][nextPos.y]->visited = true;
		

			pos = nextPos;
		}
	}
	*/

	void getVisitedNeighbors(std::vector<sf::Vector2i>& positions, sf::Vector2i position) {
		if (position.x < 0 || position.y < 0)
			return;

		if (position.x + 1 < height) {
			if (tiles[position.x + 1][position.y]->visited)
				positions.push_back({ position.x + 1, position.y });
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
				positions.push_back({ position.x + 1, position.y });
		//		tiles[position.x + 1][position.y]->changeColor(sf::Color::Red);
			}
		}

		if (position.x - 1 >= 0) {
			if (!tiles[position.x - 1][position.y]->visited) {
				positions.push_back({ position.x - 1, position.y });
			//	tiles[position.x - 1][position.y]->changeColor(sf::Color::Red);
			}
		}

		if (position.y + 1 < width) {
			if (!tiles[position.x][position.y + 1]->visited) {
				positions.push_back({ position.x, position.y + 1 });
				//tiles[position.x][position.y + 1]->changeColor(sf::Color::Red);
			}
		}

		if (position.y - 1 >= 0) {
			if (!tiles[position.x][position.y - 1]->visited) {
				positions.push_back({ position.x, position.y - 1 });
			//	tiles[position.x][position.y - 1]->changeColor(sf::Color::Red);
			}
		}
	}

	void primsAlgorithm() {
		std::vector<sf::Vector2i> neighbors;
		std::vector<sf::Vector2i> visited;
		sf::Vector2i pos = { 0,0 };
		sf::Vector2i nextPos;
		unsigned int posVector;

		getUnVisitedNeighbors(neighbors, pos);
		tiles[pos.x][pos.x]->visited = true;

		srand(time(NULL));


		while (neighbors.size()) {
			posVector = rand() % neighbors.size();
			nextPos = neighbors[posVector];

			neighbors.erase(neighbors.begin() + posVector);

			//getUnVisitedNeighbors(neighbors, nextPos);

		//	tiles[nextPos.x][nextPos.y]->changeColor(sf::Color(80, 228, 0));
			if (tiles[nextPos.x][nextPos.y]->visited) {
			//	tiles[nextPos.x][nextPos.y]->changeColor(sf::Color(20, 5, 40));
				continue;
			}

			getUnVisitedNeighbors(neighbors, nextPos);

			tiles[nextPos.x][nextPos.y]->visited = true;
		//	tiles[nextPos.x][nextPos.y]->changeColor(sf::Color::Blue);
//			tiles[nextPos.x][nextPos.y]->changeColor();


			visited.clear();
			getVisitedNeighbors(visited, nextPos);

			posVector = rand() % visited.size();
			pos = visited[posVector];

			if (pos.x < nextPos.x)
				tiles[nextPos.x][nextPos.y]->borderLeft = false;
			else if (pos.x > nextPos.x)
				tiles[nextPos.x][nextPos.y]->borderRight = false;
			else if (pos.y < nextPos.y)
				tiles[nextPos.x][nextPos.y]->borderTop = false;
			else if (pos.y > nextPos.y)
				tiles[nextPos.x][nextPos.y]->borderBottom = false;

	//		window.clear();
		//	draw();
			//window.display();
		}
	}
};