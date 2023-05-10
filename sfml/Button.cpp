#include "Button.h"

// CONSTRUCTOR & DECONSTRUCTOR
Button::Button(sf::Vector2f size, sf::Vector2f position, std::shared_ptr<sf::Font> font, std::string text) {
	Drawable::createTexture(size);
	Drawable::setPosition(position);

	this->textLabel = std::make_shared<TextLabel>(text, font);

	this->button.setSize(size);
	setColor(sf::Color(0, 0, 0, 127));
	setListeners(nullptr);
	this->isClicked = false;
	
	TextLabel::setFont(font);
	TextLabel::setText(text);
	sf::Vector2f buttonSize = this->button.getSize();

	TextLabel::setTextPositionRelative({ buttonSize.x / 2, buttonSize.y / 2 });
	draw();
}
Button::~Button() {}


// PUBLIC SECTION
void Button::setFontSize(unsigned short size) {
	TextLabel::setFontSize(size);
	sf::Vector2f buttonSize = this->button.getSize();
	TextLabel::setTextPositionRelative({ buttonSize.x / 2, buttonSize.y / 2 });
	draw();
}

void Button::setColor(sf::Color color) {
	setNormalColor(color);
	setHoverColor(color);
	setClickColor(color);
}
void Button::setNormalColor(sf::Color color) {
	this->normalColor = color;
	this->button.setFillColor(normalColor);
	draw();
}
void Button::setHoverColor(sf::Color color) {
	this->hoverColor = color;
}
void Button::setClickColor(sf::Color color) {
	this->clickColor = color;
}

void Button::setListeners(std::function<void()> action) {
	setOnMouseClick(action);
	setOnMouseRelease(action);
}
void Button::setOnMouseClick(std::function<void()> onClick) {
	this->actionOnMouseClick = onClick;
}
void Button::setOnMouseRelease(std::function<void()> onMouseRelease) {
	this->actionOnMouseRelease = onMouseRelease;
}

void Button::onClick(sf::Vector2f mousePosition){
	if (!Drawable::contains(mousePosition))
		return;

	this->button.setFillColor(this->clickColor);
	this->isClicked = true;
	draw();

	if(this->actionOnMouseClick)
		this->actionOnMouseClick();
}
void Button::onMouseMove(sf::Vector2f mousePosition){
	if (this->isClicked)
		return;

	if (Drawable::contains(mousePosition)) {
		this->button.setFillColor(this->hoverColor);
		draw();
		return;
	}
	this->button.setFillColor(this->normalColor);
	draw();
}
void Button::onMouseReleased(sf::Vector2f mousePosition){
	if (contains(mousePosition)) 
		this->button.setFillColor(this->hoverColor);
	else 
		this->button.setFillColor(this->normalColor);

	draw();

	if (this->actionOnMouseRelease && this->isClicked) {
		this->isClicked = false;
		this->actionOnMouseRelease();
	}
	else if (this->isClicked)
		this->isClicked = false;
}
void Button::draw() {
	Drawable::clearTexture();
	Drawable::draw(&this->button);
	Drawable::draw(TextLabel::getDrawable());
}
sf::Drawable* Button::getDrawable() {
	return Drawable::getDrawable();
}