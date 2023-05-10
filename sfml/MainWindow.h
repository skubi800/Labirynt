#pragma once
#include "Common.h"
#include "Window.h"
#include "Maze.h"
#include "MazeSolver.h"

class MainWindow : public Window{

	IMainMenu* menu;

	std::shared_ptr<SquareMaze> maze;
	std::shared_ptr<SquareMazeSolver> solver;

public:
	MainWindow(int width, int height, int resolution, int borderSize, short frameLimit);
	~MainWindow();

	void setMenu(IMainMenu *menu);
	void updateEvents();
};