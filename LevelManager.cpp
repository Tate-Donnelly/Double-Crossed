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
	new Player;
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
			Player* p = (Player*) li->currentObject();
			//Resets the player's values and view objects
			p->valueReset();
		}
		li->next();
	}

	setLevelIndex(levelID);
	switch (levelID) {
	case 0:
		new LevelEnd(df::Vector(30, 13));
		new HealthPack(df::Vector(30, 5));
		new Enemy(df::Vector(50,13),true);
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


void LevelManager::drawContainer() {
	new Obstacle(df::Vector(78, 0), df::BLACK, "container wall h");
	new Obstacle(df::Vector(78, 27), df::BLACK, "container wall h");
	new Obstacle(df::Vector(7, 23.5), df::BLACK, "container wall v");
	new Obstacle(df::Vector(82, 23.5), df::BLACK, "container wall v");
}