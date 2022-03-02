#include "LevelManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "ViewObject.h"
#include "Player.h"
#include "Obstacle.h"
#include "HealthPack.h"
#include "EventView.h"
#include "LevelEnd.h"
#include "Enemy.h"
#include "FOV.h"

LevelManager::LevelManager() {
	setType("LevelManager");
	setLevelIndex(0);
}

//Get the instance of the LevelManager
LevelManager& LevelManager::getInstance() {
	static LevelManager levelManager;
	return levelManager;
}
int LevelManager::startUp() {
	p.start();
	loadLevel(0);
	df::Manager::startUp();
	return 0;
}

void LevelManager::shutDown() {
	df::Manager::shutDown();
}

//Sets level_index
void LevelManager::setLevelIndex(int level) {
	level_index = level;
}

//Gets level_index
int LevelManager::getLevelIndex()  const {
	return level_index;
}



//Loads in selected level
int LevelManager::loadLevel(int levelID) {
	df::ObjectListIterator* li = new df::ObjectListIterator(new df::ObjectList(WM.getAllObjects()));
	while (!li->isDone()) {
		if (!m_protectedObjects.contains(li->currentObject())) {
			WM.markForDelete(li->currentObject());
		}
		if ((getLevelIndex() == levelID) && (li->currentObject()->getType() == "Player")) {//If the level was reset
			//Player* p = (Player*) li->currentObject();
			//Resets the player's values and view objects
			p.valueReset();
		}
		li->next();
	}

	setLevelIndex(levelID);
	switch (levelID) {
	case 0:
		drawBarrier(20, 3);
		drawBarrier(20, 18);
		drawBarrier(100, 3);
		drawBarrier(100, 18);
		drawBarrier(120, 3);
		drawBarrier(120, 18);
		drawBox(55, 15);
		drawContainer(5,3, 120, 24);
		p.setPosition(df::Vector(12, 22));
		//new LevelEnd(df::Vector(30, 13));
		//new HealthPack(df::Vector(30, 5));
		new Enemy(df::Vector(60, 7 ), true, backAndForth);
		break;
	case 1:
		new LevelEnd(df::Vector(50, 13));
		break;
	case 2:
		new LevelEnd(df::Vector(30, 13));
		break;
	default:
		return 1;
	}
}

void LevelManager::insertProtected(df::Object* object) {
	m_protectedObjects.insert(object);
}

int LevelManager::nextLevel() {
	if (getLevelIndex() == totalLevels-1) {//Error if it's on the last level
		return 1;
	}
	loadLevel(getLevelIndex()+1);
	return 0;
}
void LevelManager::resetLevel() {
	loadLevel(getLevelIndex());
}

void LevelManager::drawBox(float x, float y) {
	new Obstacle(df::Vector(x, y), df::YELLOW, "box");
}

void LevelManager::drawBarrier(float x, float y) {
	new Obstacle(df::Vector(x, y+4.5), df::YELLOW, "container barrier wall v");
	new Obstacle(df::Vector(x+5, y + 4.5), df::YELLOW, "container barrier wall v");
	new Obstacle(df::Vector(x+2.5, y), df::YELLOW, "container barrier wall h");
	new Obstacle(df::Vector(x + 2.5, y+9), df::YELLOW, "container barrier wall h");
}

void LevelManager::drawContainer(float x, float y, int length, int height)
{
	for (int i = 0; i < length; i = i + 40) {
		drawContainerH(x+i, y);
		drawContainerH(x + i, y+height);
	}
	for (int i = 0; i < height; i = i + 12) {
		drawContainerV(x,y + i);
		drawContainerV(x+length, y + i);
	}
}

void LevelManager::drawContainerH(float x, float y) {
	new Obstacle(df::Vector(x+20, y), df::YELLOW, "container wall h");
}
void LevelManager::drawContainerV(float x, float y) {
	new Obstacle(df::Vector(x, y+6), df::YELLOW, "container wall v");
}