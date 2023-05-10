#include "MainWindow.h"


// CONSTRUCTOR & DECONSTRUCTOR
MainWindow::MainWindow(int width, int height, int resolution, int borderSize, short frameLimit)
	: Window(frameLimit) {
	this->menu = nullptr;
	int totalWidth = width * resolution + (width + 1) * borderSize;
	int totalHeight = height * resolution + (height + 1) * borderSize;
	Window::setWindowResolution(totalHeight, totalWidth);

	sf::Vector2i startingPoint;
	srand(time(NULL));
	startingPoint.x = rand() % width;
	startingPoint.y = rand() % height;


	this->maze = std::make_shared<SquareMaze>(width, height, resolution, borderSize, sf::Color(108, 108, 108));
	this->solver = std::make_shared<SquareMazeSolver>(this->maze, startingPoint);
	this->Window::drawableContainer.push_back(this->maze);
	while (this->solver->solvePrims());
}
MainWindow::~MainWindow() {}


// PULIC SECTION
void MainWindow::setMenu(IMainMenu *menu){
	this->menu = menu;
}
void MainWindow::updateEvents() {
	while (this->window.pollEvent(this->event)) {
		switch (this->event.type) {
		case sf::Event::Closed: {
			if (this->menu)
				this->menu->showMenu();
			this->window.close();
			break;
		}
		}
	}
}