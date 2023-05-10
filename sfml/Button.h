#pragma once
#include "Common.h"
#include "Events.h"
#include "Drawable.h"
#include "TextLabel.h"

class Button : public Clickable, public MouseMove, public MouseReleased, public TextLabel {

	sf::RectangleShape button;
	std::shared_ptr<TextLabel> textLabel;

	bool isClicked;
	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color clickColor;

	std::function<void()> actionOnMouseClick;
	std::function<void()> actionOnMouseRelease;

public:
	Button(sf::Vector2f size, sf::Vector2f position, std::shared_ptr<sf::Font> font, std::string text);
	~Button();

	void setFontSize(unsigned short size);

	void setColor(sf::Color color);
	void setNormalColor(sf::Color color);
	void setHoverColor(sf::Color color);
	void setClickColor(sf::Color color);
	
	void setListeners(std::function<void()> action);
	void setOnMouseClick(std::function<void()> onClick);
	void setOnMouseRelease(std::function<void()> onMouseRelease);

	void onClick(sf::Vector2f);
	void onMouseMove(sf::Vector2f);
	void onMouseReleased(sf::Vector2f);
	void draw();
	sf::Drawable* getDrawable();
};