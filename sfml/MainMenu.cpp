#include "MainMenu.h"

// PRIVATE SECTION
void MainMenu::initialize(std::string title){
	float sizeOfCell = 12;
	float borderSize = 2;
	short x, y;
	double w = (this->Window::width - borderSize) / (sizeOfCell + borderSize);
	
	while ((int)w - w != 0) {
		this->width += borderSize;
		w = (this->width - borderSize) / (sizeOfCell + borderSize);
	}

	x = w;
	w = (this->Window::height - borderSize) / (sizeOfCell + borderSize);

	while ((int)w - w != 0) {
		this->height += borderSize;
		w = (this->height - borderSize) / (sizeOfCell + borderSize);
	}
	
	y = w;

	this->backgroundMaze = std::make_shared<SquareMaze>(x, y, sizeOfCell, borderSize, sf::Color(108, 108, 108));
	this->mazeSolver = std::make_shared<SquareMazeSolver>(this->backgroundMaze, sf::Vector2i(x / 2, y / 2));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	Window::setWindowResolution(this->height, this->width);
	Window::createWindow(title, settings);
	Window::setDimmer(110);

	loadFont("CourierPrime-Regular.ttf");
	
	// GRAPHICAL INTERFACE
	std::shared_ptr<Button> test = std::make_shared<Button>(sf::Vector2f(200, 70), sf::Vector2f{ 450,475 }, this->font, "Generate");
	test->setNormalColor(sf::Color(0, 0, 0, 50));
	test->setClickColor(sf::Color(0, 255, 0, 70));
	test->setHoverColor(sf::Color(0, 255, 0, 80));
	test->setFontSize(33);
	test->setOnMouseRelease([&]() {
		this->window.setVisible(false);
		this->runMainWindow();
	});
	
	listener.add(test);

	this->drawableContainer.push_back(test);
	
	std::shared_ptr<TextLabel> titleLabel = std::make_shared<TextLabel>("Maze Generator", this->font);
	titleLabel->setFontSize(55);
	titleLabel->setLetterSpaceing(1.5);
	titleLabel->setTextPositionRelative({ float(this->Window::width / 2),60 });
	
	std::shared_ptr<TextLabel> sizes = std::make_shared<TextLabel>("Dimensions of maze\nHeight:\nWidth:\nCell size:", this->font);
	sizes->setFontSize(33);
	sizes->setTextPosition({ 20,150 });
	
	std::shared_ptr<TextLabel> heightLabel = std::make_shared<TextLabel>();
	heightLabel->setFont(this->font);
	heightLabel->setFontSize(33);
	heightLabel->setTextPosition({ 230,187 });

	std::shared_ptr<TextLabel> widthLabel = std::make_shared<TextLabel>();
	widthLabel->setFont(this->font);
	widthLabel->setFontSize(33);
	widthLabel->setTextPosition({ 230,224 });

	std::shared_ptr<TextLabel> sizeLabel = std::make_shared<TextLabel>();
	sizeLabel->setFont(this->font);
	sizeLabel->setFontSize(33);
	sizeLabel->setTextPosition({ 230,261 });

	sliderHeight = std::make_shared<Slider>(sf::Vector2f{ 150,15 },
		sf::Vector2f{ 300, 204 }, 24, heightLabel, 16);
	
	sliderWidth = std::make_shared<Slider>(sf::Vector2f{ 150,15 },
		sf::Vector2f{ 300, 242 }, 24, widthLabel, 16);
	
	sliderSize = std::make_shared<Slider>(sf::Vector2f{ 150,15 },
		sf::Vector2f{ 300, 280 }, 8, sizeLabel, 2);

	listener.add(sliderHeight);
	listener.add(sliderWidth);
	listener.add(sliderSize);

	this->drawableContainer.push_back(sliderSize);
	this->drawableContainer.push_back(sliderHeight);
	this->drawableContainer.push_back(sliderWidth);
	this->drawableContainer.push_back(heightLabel);
	this->drawableContainer.push_back(widthLabel);
	this->drawableContainer.push_back(sizeLabel);
	this->drawableContainer.push_back(titleLabel);
	this->drawableContainer.push_back(sizes);
}


// CONSTRUCTOR & DECONSTRUCTOR
MainMenu::MainMenu(std::string title, int width, int height, short frameLimit)
	: Window(width, height, frameLimit) {
	initialize(title);
}
MainMenu::~MainMenu() {}


// PUBLIC SECTION
void MainMenu::loadFont(std::string filename) {
	this->font = std::make_shared<sf::Font>();
	this->font->loadFromFile(filename);
}
void MainMenu::update() {
	updateEvents();

	this->Window::window.draw(*this->backgroundMaze->getDrawable());
	this->mazeSolver->solvePrims();
	this->mazeSolver->solvePrims();
	this->Window::window.draw(this->Window::screenDimmer);

	for (auto i : this->Window::drawableContainer) {
		this->Window::window.draw(*i->getDrawable());
	}
}
void MainMenu::updateEvents() {
	while (this->Window::window.pollEvent(this->Window::event)) {
		switch (this->event.type) {
		case sf::Event::Closed: {
			this->Window::window.close();
			break;
		}
		case sf::Event::MouseButtonPressed: {
			this->listener.onClick((sf::Vector2f)sf::Mouse::getPosition(this->Window::window));
			break;
		}
		case sf::Event::MouseButtonReleased: {
			this->listener.onMouseReleased((sf::Vector2f)sf::Mouse::getPosition(this->Window::window));
			break;
		}
		case sf::Event::MouseMoved: {
			this->listener.onMouseMove((sf::Vector2f)sf::Mouse::getPosition(this->Window::window));
			break;
		}
		}
	}
}
void MainMenu::run() {
	Window::run();
}
void MainMenu::runMainWindow() {
	int width = this->sliderWidth->getValue();
	int height = this->sliderHeight->getValue();
	int resolution = this->sliderSize->getValue();
	int borderSize = 2;

	this->mainWindow = std::make_shared<MainWindow>(width, height, resolution, borderSize,this->frameLimit);
	mainWindow->setMenu(this);
	mainWindow->createWindow("Generated Labyrinth");
	mainWindow->run();
}

void MainMenu::showMenu(){
	update();
	this->Window::window.setVisible(true);
}