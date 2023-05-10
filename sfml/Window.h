#pragma once
#include "Common.h"
#include "Drawable.h"

class Window {
protected:
	sf::RenderWindow window;
	int height;
	int width;

	sf::Event event;

	short frameLimit;

	sf::RectangleShape screenDimmer;
	std::vector<std::shared_ptr<Drawable>> drawableContainer;

	sf::Clock clock;
	int elapsedMili;	

public:
	Window(int width, int height, short frameLimit);
	Window(short frameLimit);
	virtual ~Window();

	void setDimmer(unsigned short value);
	void setWindowResolution(unsigned int height, unsigned int width);
	void createWindow(std::string title);
	void createWindow(std::string title, sf::ContextSettings settings);
	virtual void update();
	virtual void updateEvents();
	void run();
};