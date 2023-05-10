#include "Listener.h"

// CONSTRUCTOR & DECONSTRUCTOR
Listener::Listener() {}
Listener::~Listener() {}


// PUBLIC SECTION
void Listener::onClick(sf::Vector2f mousePosition) {
	for (std::shared_ptr<Clickable> i : this->clickListener) {
		i->onClick(mousePosition);
	}
}
void Listener::onMouseReleased(sf::Vector2f mousePosition){
	for (std::shared_ptr<MouseReleased> i : this->mouseReleaseListener) {
		i->onMouseReleased(mousePosition);
	}
}
void Listener::onMouseMove(sf::Vector2f mousePosition) {
	for (std::shared_ptr<MouseMove> i : this->mouseMoveListener) {
		i->onMouseMove(mousePosition);
	}
}
void Listener::add(std::shared_ptr<Button> listener){
	this->clickListener.push_back(listener);
	this->mouseMoveListener.push_back(listener);
	this->mouseReleaseListener.push_back(listener);
}
void Listener::add(std::shared_ptr<Slider> listener) {
	this->clickListener.push_back(listener);
	this->mouseMoveListener.push_back(listener);
	this->mouseReleaseListener.push_back(listener);
}