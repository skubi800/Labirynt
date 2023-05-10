#pragma once
#include "Common.h"

class Drawable {
	std::unique_ptr<sf::Sprite> sprite;
	std::unique_ptr<sf::RenderTexture> renderTexture;

protected:
	void draw(sf::Drawable* toDraw);
	virtual void setPosition(sf::Vector2f pos);
	void createTexture(sf::Vector2f size);
	void clearTexture();
	sf::FloatRect getSpriteGlobalBounds();
	bool contains(sf::Vector2f mousePosition);
	void displayTexture();
	sf::Vector2f convertToLocal(sf::Vector2f mousePosition);

public:
	Drawable();
	~Drawable();

	virtual sf::Drawable* getDrawable();
};