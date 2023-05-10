#pragma once
#include "Common.h"

#include "Slider.h"
#include "Button.h"
#include "Listener.h"
#include "Maze.h"
#include "MazeSolver.h"
#include "Window.h"
#include "TextLabel.h"
#include "MainWindow.h"

class MainMenu : protected Window, public IMainMenu {

	std::shared_ptr<SquareMaze> backgroundMaze;
	std::shared_ptr<SquareMazeSolver> mazeSolver;

	Listener listener;

	std::shared_ptr<sf::Font> font;

	std::shared_ptr<Slider> sliderHeight;
	std::shared_ptr<Slider> sliderWidth;
	std::shared_ptr<Slider> sliderSize;

	std::shared_ptr<MainWindow> mainWindow;

	void initialize(std::string);

public:
	MainMenu(std::string title, int width, int height, short frameLimit = 30);
	~MainMenu();

	void loadFont(std::string filename);
	void update();
	void updateEvents();
	void run();
	void runMainWindow();
	void showMenu();
};