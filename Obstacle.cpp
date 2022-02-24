#include "Obstacle.h"
Obstacle::Obstacle() {
	Obstacle(df::Vector(), df::Vector(), 0, 0, sf::Color::Yellow, false);
}
Obstacle::Obstacle(df::Vector pos, df::Vector corner, float horizontal, float vertical, sf::Color color, bool transparent) {
	setCorner(corner);
	setHorizontal(horizontal);
	setVertical(vertical);
	setColor(color);
	setPosition(pos);
	setSolidness(df::HARD);
	setAltitude(3);
	setBox(df::Box(corner, horizontal, vertical));
}

void Obstacle::setCorner(df::Vector corner) {
	m_corner = corner;
}
df::Vector Obstacle::getCorner() {
	return m_corner;
}

void Obstacle::setHorizontal(float new_horizontal) {
	m_horizontal = new_horizontal;
}
float Obstacle::getHorizontal() {
	return m_horizontal;
}

void Obstacle::setVertical(float new_vertical) {
	m_vertical = new_vertical;
}
float Obstacle::getVertical() {
	return m_vertical;
}

void Obstacle::setColor(sf::Color new_color) {
	m_color = new_color;
}
sf::Color Obstacle::getColor() {
	return m_color;
}

void Obstacle::setTransparent(bool isTransparent) {
	m_isTransparent = isTransparent;
}
bool Obstacle::getTransparent() {
	return m_isTransparent;
}

int Obstacle::draw(){
	getBox().draw(m_color, m_isTransparent);
	return 0;
}