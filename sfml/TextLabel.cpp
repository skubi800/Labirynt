#include "TextLabel.h"


// CONSTRUCTOR & DECONSTRUCTOR
TextLabel::TextLabel(std::string text, std::shared_ptr<sf::Font> font, sf::Vector2f position) {
	this->text = std::make_shared<sf::Text>();
	setFont(font);
	setText(text);
	setPosition(position);
}
TextLabel::TextLabel() {
	this->text = std::make_shared<sf::Text>();
}
TextLabel::~TextLabel() {}


// PUBLIC SECTION
void TextLabel::setFont(std::shared_ptr<sf::Font> font, unsigned short fontSize) {
	if(font)
		this->text->setFont(*font);
	setFontSize(fontSize);
}
void TextLabel::setFontSize(unsigned short fontSize) {
	this->text->setCharacterSize(fontSize);
}
void TextLabel::setText(std::string text, sf::Text::Style style) {
	this->text->setString(text);
	setFontStyle(style);
}
void TextLabel::setFontStyle(sf::Text::Style style) {
	this->text->setStyle(style);
}
void TextLabel::setTextPosition(sf::Vector2f position) {
	this->text->setPosition(position);
}
void TextLabel::setTextPositionRelative(sf::Vector2f position) {
	setTextPosition({ 0,0 });
	sf::FloatRect textBounds = this->text->getGlobalBounds();
	position.x -= (textBounds.width / 2) + textBounds.left;
	position.y -= (textBounds.height / 2) + textBounds.top;
	setTextPosition(position);
}
void TextLabel::setLetterSpaceing(float value) {
	this->text->setLetterSpacing(value);
}
void TextLabel::setTextColor(sf::Color color) {
	this->text->setFillColor(color);
}
sf::FloatRect TextLabel::getGlobalBounds() {
	return this->text->getGlobalBounds();
}
sf::Drawable* TextLabel::getDrawable() {
	return &*this->text;
}