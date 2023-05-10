#include "Drawable.h"

// CONSTRUCTOR & DECONSTRUCTOR
Drawable::Drawable() : sprite(nullptr), renderTexture(nullptr) {}
Drawable::~Drawable() {}


// PROTECTED SECTION
void Drawable::setPosition(sf::Vector2f pos) {
	if (this->sprite)
		this->sprite->setPosition(pos);
}
void Drawable::createTexture(sf::Vector2f size) {
	this->renderTexture = std::make_unique<sf::RenderTexture>();
	this->renderTexture->create(size.x, size.y);

	if (!this->sprite)
		this->sprite = std::make_unique<sf::Sprite>();

	this->sprite->setTexture(this->renderTexture->getTexture());		
}
void Drawable::clearTexture() {
	if(renderTexture)
		this->renderTexture->clear(sf::Color(0, 0, 0, 0));
}
sf::FloatRect Drawable::getSpriteGlobalBounds() {
	if(sprite)
		return this->sprite->getGlobalBounds();
	return { 0,0,0,0 };
}
void Drawable::draw(sf::Drawable* toDraw) {
	if (this->renderTexture)
		this->renderTexture->draw(*toDraw);
}
bool Drawable::contains(sf::Vector2f mousePosition) {
	if (this->sprite && this->sprite->getGlobalBounds().contains(mousePosition))
		return true;
	return false;
}
void Drawable::displayTexture() {
	if(this->renderTexture)
		this->renderTexture->display();
}
sf::Vector2f Drawable::convertToLocal(sf::Vector2f mousePosition) {
	sf::FloatRect rect = getSpriteGlobalBounds();
	mousePosition.x -= rect.left;
	mousePosition.y -= rect.top;
	return mousePosition;
}


// PUBLIC SECTION
sf::Drawable* Drawable::getDrawable() {
	displayTexture();
	return &*this->sprite;
}