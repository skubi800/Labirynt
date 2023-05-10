#pragma once
#include "Common.h"
#include "Maze.h"

class Prims {

	sf::Vector2i position;
	sf::Vector2i nextPos;
	unsigned short positionVector;

	std::vector<sf::Vector2i> neighbors;
	std::vector<sf::Vector2i> visited;

	std::shared_ptr<SquareMaze> maze;

	std::random_device dev;
	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> dist;

public:
	Prims(std::shared_ptr<SquareMaze> maze, sf::Vector2i startingPoint = { 0,0 }) : maze(maze) {
		position = startingPoint;
		nextPos = startingPoint;
		positionVector = 0;

		getUnVisitedNeighbors(neighbors, position);
		this->maze->tiles[nextPos.x][nextPos.y]->visited = true;

		rng = std::mt19937(dev());
	}

	~Prims() {}

	bool solve() {
		if (!neighbors.size()) return false;

		positionVector = dist(rng) % neighbors.size();
		nextPos = neighbors[positionVector];

		neighbors.erase(neighbors.begin() + positionVector);
		getUnVisitedNeighbors(neighbors, nextPos);

		this->maze->tiles[nextPos.x][nextPos.y]->visited = true;
		this->maze->changeColorOfTile(nextPos, this->maze->colorOfTiles);

		visited.clear();
		getVisitedNeighbors(visited, nextPos);

		position = visited[dist(rng) % visited.size()];

		if (position.x < nextPos.x) {
			this->maze->tiles[nextPos.x][nextPos.y]->borderLeft = false;
			this->maze->drawLeftBorder(nextPos);

			if (nextPos.x - 1 >= 0)
				this->maze->tiles[nextPos.x - 1][nextPos.y]->borderRight = false;
		}
		else if (position.x > nextPos.x) {
			this->maze->tiles[nextPos.x][nextPos.y]->borderRight = false;
			this->maze->drawRightBorder(nextPos);

			if (nextPos.x + 1 < this->maze->width)
				this->maze->tiles[nextPos.x + 1][nextPos.y]->borderLeft = false;
		}
		else if (position.y < nextPos.y) {
			this->maze->tiles[nextPos.x][nextPos.y]->borderTop = false;
			this->maze->drawTopBorder(nextPos);

			if (nextPos.y - 1 >= 0)
				this->maze->tiles[nextPos.x][nextPos.y - 1]->borderBottom = false;
		}
		else if (position.y > nextPos.y) {
			this->maze->tiles[nextPos.x][nextPos.y]->borderBottom = false;
			this->maze->drawBottomBorder(nextPos);

			if (nextPos.y + 1 < this->maze->height)
				this->maze->tiles[nextPos.x][nextPos.y + 1]->borderTop = false;
		}

		return true;
	}

	void getUnVisitedNeighbors(std::vector<sf::Vector2i>& positions, sf::Vector2i position) {
		if (position.x < 0 || position.y < 0)
			return;

		if (position.x + 1 < this->maze->width) {
			if (!this->maze->tiles[position.x + 1][position.y]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x + 1, position.y)) == positions.end()) {
					positions.push_back({ position.x + 1, position.y });
					this->maze->changeColorOfTile({ position.x + 1, position.y });
				}
			}
		}

		if (position.x - 1 >= 0) {
			if (!this->maze->tiles[position.x - 1][position.y]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x - 1, position.y)) == positions.end()) {
					positions.push_back({ position.x - 1, position.y });
					this->maze->changeColorOfTile({ position.x - 1, position.y });
				}
			}
		}

		if (position.y + 1 < this->maze->height) {
			if (!this->maze->tiles[position.x][position.y + 1]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x, position.y + 1)) == positions.end()) {
					positions.push_back({ position.x, position.y + 1 });
					this->maze->changeColorOfTile({ position.x, position.y + 1 });
				}
			}
		}

		if (position.y - 1 >= 0) {
			if (!this->maze->tiles[position.x][position.y - 1]->visited) {
				if (std::find(positions.begin(), positions.end(), sf::Vector2i(position.x, position.y - 1)) == positions.end()) {
					positions.push_back({ position.x, position.y - 1 });
					this->maze->changeColorOfTile({ position.x, position.y - 1 });
				}
			}
		}
	}

	void getVisitedNeighbors(std::vector<sf::Vector2i>& positions, sf::Vector2i& position) {
		if (position.x < 0 || position.y < 0)
			return;

		if (position.x + 1 < this->maze->width) {
			if (this->maze->tiles[position.x + 1][position.y]->visited)
				positions.push_back({ position.x + 1, position.y });
		}

		if (position.x - 1 >= 0) {
			if (this->maze->tiles[position.x - 1][position.y]->visited)
				positions.push_back({ position.x - 1, position.y });
		}

		if (position.y + 1 < this->maze->height) {
			if (this->maze->tiles[position.x][position.y + 1]->visited)
				positions.push_back({ position.x, position.y + 1 });
		}

		if (position.y - 1 >= 0) {
			if (this->maze->tiles[position.x][position.y - 1]->visited)
				positions.push_back({ position.x, position.y - 1 });
		}
	}

};


class SquareMazeSolver {
	std::shared_ptr<Prims> prims;

public:
	SquareMazeSolver(std::shared_ptr<SquareMaze> maze, sf::Vector2i startingPoint) {
		prims = std::make_shared<Prims>(maze, startingPoint);
	}

	~SquareMazeSolver() {}

	bool solvePrims() {
		return prims->solve();
	}
};