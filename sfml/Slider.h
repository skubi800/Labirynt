#pragma once
#include "Common.h"
#include "Drawable.h"
#include "Events.h"
#include "TextLabel.h"

class Slider : public Drawable, public Clickable, public MouseMove, public MouseReleased {

	sf::RectangleShape indicator;
	sf::RectangleShape sliderBar;
	
	sf::FloatRect boundsOfSlider;
	
	std::shared_ptr<TextLabel> displayer;

	bool isClicked;
	unsigned short numberOfPositions;
	unsigned short step;
	float positionStep;

	unsigned short value;

public:
	Slider(sf::Vector2f size, sf::Vector2f position, unsigned short numberOfPositions,
		std::shared_ptr<TextLabel> displayer, unsigned int step = 8);
	~Slider();

	void onClick(sf::Vector2f mousePosition);
	void onMouseMove(sf::Vector2f mousePosition);
	void onMouseReleased(sf::Vector2f mousePosition);
	void setIndicatorPosition(sf::Vector2f);

	unsigned short getValue();

	void draw();
};