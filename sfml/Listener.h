#pragma once
#include "Common.h"
#include "Button.h"
#include "Slider.h"

class Listener{
	std::vector<std::shared_ptr<Clickable>> clickListener;
	std::vector<std::shared_ptr<MouseMove>> mouseMoveListener;
	std::vector<std::shared_ptr<MouseReleased>> mouseReleaseListener;

public:
	Listener();
	virtual ~Listener();

	void onClick(sf::Vector2f mousePosition);
	void onMouseReleased(sf::Vector2f mousePosition);
	void onMouseMove(sf::Vector2f mousePosition);
	void add(std::shared_ptr<Button> listener);
	void add(std::shared_ptr<Slider> listener);
};