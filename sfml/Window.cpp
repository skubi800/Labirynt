#include "Window.h"

// CONSTRUCTOR & DECONSTRUCTOR
Window::Window(int width, int height, short frameLimit)
	: width(width), height(height), frameLimit(frameLimit) {
	this->elapsedMili = 0;
	setWindowResolution(height, width);
}
Window::Window(short frameLimit) : frameLimit(frameLimit){
	this->elapsedMili = 0;
}
Window::~Window() {}


// PUBLIC SECTION
void Window::setDimmer(unsigned short value) {
	this->screenDimmer.setFillColor(sf::Color(0, 0, 0, value));
}
void Window::setWindowResolution(unsigned int height, unsigned int width) {
	unsigned int windowWidth = sf::VideoMode::getDesktopMode().width;
	unsigned int windowHeight = sf::VideoMode::getDesktopMode().height;

	if (height <= windowHeight)
		windowHeight = height;

	if (width <= windowWidth)
		windowWidth = width;

	this->height = windowHeight;
	this->width = windowWidth;

	this->screenDimmer.setSize({ (float)this->width, (float)this->height });
}
void Window::createWindow(std::string title) {
	this->window.create(sf::VideoMode(this->width, this->height), title, sf::Style::Titlebar | sf::Style::Close);
}
void Window::createWindow(std::string title, sf::ContextSettings settings) {
	this->window.create(sf::VideoMode(this->width, this->height), title, sf::Style::Titlebar | sf::Style::Close, settings);
}
void Window::update() {
	updateEvents();

	for (auto i : this->drawableContainer) {
		this->window.draw(*i->getDrawable());
	}
}
void Window::updateEvents() {
	while (this->window.pollEvent(this->event)) {
		switch (this->event.type) {
		case sf::Event::Closed: {
			this->window.close();
			break;
		}
		}
	}
}
void Window::run() {

	while (this->window.isOpen()) {
		this->window.clear();
		update();
		this->window.display();

		//this->elapsedMili = this->clock.restart().asMilliseconds();
		//std::this_thread::sleep_for(std::chrono::milliseconds((1000 - (frameLimit * elapsedMili)) / frameLimit));
		//this->clock.restart();
	}
}