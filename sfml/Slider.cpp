#include "Slider.h"

// CONSTRUCTOR & DECONSTRUCTOR
Slider::Slider(sf::Vector2f size, sf::Vector2f position, unsigned short numberOfPositions,
	std::shared_ptr<TextLabel> displayer, unsigned int step) : displayer(displayer) {
	this->isClicked = false;
	this->numberOfPositions = numberOfPositions - 1;
	this->step = step;

	Drawable::createTexture(size);
	Drawable::setPosition(position);
	
	float heightOfBar = size.y * 3.0 / 5.0;

	float sizeOfIndicator = 3 * heightOfBar / 4;
	this->positionStep = (size.x - sizeOfIndicator) / this->numberOfPositions;

	this->indicator.setFillColor(sf::Color(44, 211, 73, 255));
	this->indicator.setSize({ sizeOfIndicator, size.y });

	this->sliderBar.setFillColor(sf::Color(136, 136, 136, 200));
	size.y = heightOfBar;
	this->sliderBar.setSize(size);
	this->sliderBar.setPosition(0, heightOfBar / 3);

	this->boundsOfSlider = Drawable::getSpriteGlobalBounds();

	this->displayer->setText(std::to_string(this->step));
	this->value = this->step;

	draw();
}
Slider::~Slider() {}


// PUBLIC SECTION
void Slider::onClick(sf::Vector2f mousePosition) {
	if (this->sliderBar.getGlobalBounds().contains(Drawable::convertToLocal(mousePosition)))
		setIndicatorPosition(mousePosition);
	
	if (!this->sliderBar.getGlobalBounds().contains(Drawable::convertToLocal(mousePosition)))
		return;

	this->isClicked = true;
	this->indicator.setFillColor(sf::Color::Red);
	draw();
}
void Slider::onMouseMove(sf::Vector2f mousePosition) {
	if (!this->isClicked)
		return;

	setIndicatorPosition(mousePosition);

	draw();
}
void Slider::onMouseReleased(sf::Vector2f mousePosition) {
	if (!this->isClicked)
		return;

	this->isClicked = false;
	this->indicator.setFillColor(sf::Color(44, 211, 73, 255));
	
	draw();
}
void Slider::setIndicatorPosition(sf::Vector2f mousePosition) {
	mousePosition.x -= this->boundsOfSlider.left;
	mousePosition.x = std::floor(mousePosition.x / this->positionStep);

	float pos = mousePosition.x * this->positionStep;

	if (mousePosition.x > this->numberOfPositions)
		mousePosition.x = this->numberOfPositions;
	else if (mousePosition.x < 0)
		mousePosition.x = 0;

	this->value = (mousePosition.x + 1) * this->step;
	this->displayer->setText(std::to_string(this->value));

	sf::Vector2f sizeOfSlider = this->sliderBar.getSize();
	sf::Vector2f sizeOfIndicator = this->indicator.getSize();

	if (pos > sizeOfSlider.x - sizeOfIndicator.x)
		pos = sizeOfSlider.x - sizeOfIndicator.x;
	else if (pos < 0)
		pos = 0;

	this->indicator.setPosition(pos, 0);
}
unsigned short Slider::getValue() {
	return this->value;
}

void Slider::draw() {
	Drawable::clearTexture();
	Drawable::draw(&this->sliderBar);
	Drawable::draw(&this->indicator);
}