#pragma once
#include "Common.h"

class MouseMove {

public:
	virtual void onMouseMove(sf::Vector2f) = 0;
};

class Clickable {

public:
	virtual void onClick(sf::Vector2f) = 0;
};

class MouseReleased {

public:
	virtual void onMouseReleased(sf::Vector2f) = 0;
};