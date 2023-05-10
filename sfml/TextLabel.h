#pragma once
#include "Common.h"
#include "Drawable.h"

class TextLabel : public Drawable{
protected:
	std::shared_ptr<sf::Text> text;

public:
	TextLabel(std::string text, std::shared_ptr<sf::Font> font, sf::Vector2f position = { 0,0 });
	TextLabel();
	~TextLabel();

	void setFont(std::shared_ptr<sf::Font> font, unsigned short fontSize = 30);
	void setFontSize(unsigned short fontSize);
	void setText(std::string text, sf::Text::Style style = sf::Text::Regular);
	void setFontStyle(sf::Text::Style style);
	void setTextPosition(sf::Vector2f position);
	void setTextPositionRelative(sf::Vector2f position);
	void setLetterSpaceing(float value);
	void setTextColor(sf::Color color);
	sf::FloatRect getGlobalBounds();
	sf::Drawable* getDrawable();
};