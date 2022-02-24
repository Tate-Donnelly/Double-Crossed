#include "Level.h"
#include <SFML/Graphics.hpp>
#include "ObjectListIterator.h"

Level::Level() {
	
	
}
void Level::drawMap() {
	df::ObjectListIterator* li=new df::ObjectListIterator(&m_obstacles);
	while (!li->isDone()) {
		if (li->currentObject() != NULL) {
			li->currentObject()->draw();
		}
	}
}

int Level::insertObstacle(Obstacle *o) {
	if (m_obstacles.insert(o)) {
		return 0;
	}
	return -1;
}

int Level::removeObstacle(Obstacle* o) {
	if (m_obstacles.remove(o)) {
		return 0;
	}
	return -1;
}