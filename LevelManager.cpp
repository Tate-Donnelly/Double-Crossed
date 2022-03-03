#include "LevelManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "ViewObject.h"
#include "Player.h"
#include "Obstacle.h"
#include "Intel.h"
#include "EventView.h"
#include "LevelEnd.h"
#include "Enemy.h"
#include "FOV.h"
#include "HealthPack.h"
#include "Landmine.h"
#include "Reticle.h"

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
		Level1();
		break;
	case 1:
		Level2();
		break;
	case 2:
		Level3();
		break;
	default:
		return 1;
	}
}

void LevelManager::insertProtected(df::Object* object) {
	m_protectedObjects.insert(object);
}

int LevelManager::nextLevel() {
	//p.setActive(false);
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

void LevelManager::drawWideBox(float x, float y) {
	new Obstacle(df::Vector(x, y), df::YELLOW, "widebox");
}

void LevelManager::drawBarrier(float x, float y) {
	new Obstacle(df::Vector(x, y+4.5), df::YELLOW, "container barrier wall v");
	new Obstacle(df::Vector(x+5, y + 4.5), df::YELLOW, "container barrier wall v");
	new Obstacle(df::Vector(x+2.5, y), df::YELLOW, "container barrier wall h");
	new Obstacle(df::Vector(x + 2.5, y+9), df::YELLOW, "container barrier wall h");
}

void LevelManager::drawEntryBarrier(float x, float y) {
	new Obstacle(df::Vector(x, y + 4.5), df::YELLOW, "container barrier wall v");
	new Obstacle(df::Vector(x + 5, y + 4.5), df::YELLOW, "container barrier wall v");
	new Obstacle(df::Vector(x + 2.5, y), df::YELLOW, "container barrier wall h");
	//new Obstacle(df::Vector(x + 2.5, y + 9), df::YELLOW, "container barrier wall h");
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

void LevelManager::drawContainerDown(float x, float y, int length, int height)
{	
	drawContainerH(x, y);
	drawContainerH(x + 40, y);
	drawContainerH(x + 80, y);
	drawContainerH(x, y + height);
	drawContainerH(x + 80, y + height);
	for (int i = 0; i < height; i = i + 12) {
		drawContainerV(x, y + i);
		drawContainerV(x + length, y + i);
	}
}


void LevelManager::drawContainerUp(float x, float y, int length, int height)
{
	drawContainerH(x, y);
	drawContainerH(x + 80, y);
	drawContainerH(x, y + height);
	drawContainerH(x + 40, y+height);
	drawContainerH(x + 80, y + height);
	for (int i = 0; i < height; i = i + 12) {
		drawContainerV(x, y + i);
		drawContainerV(x + length, y + i);
	}
}


void LevelManager::drawContainerUpLeftRight(float x, float y, int length, int height)
{
	drawContainerH(x, y);
	drawContainerH(x + 80, y);
	drawContainerH(x, y + height);
	drawContainerH(x + 40, y + height);
	drawContainerH(x + 80, y + height);
	drawContainerV8(x, y);
	drawContainerV8(x + length, y);
	drawContainerV8(x, y + 16) ;
	drawContainerV8(x + length, y + 16);
}

void LevelManager::drawContainerLeft(float x, float y, int length, int height)
{
	drawContainerH(x, y);
	drawContainerH(x + 40, y);
	drawContainerH(x + 80, y);
	drawContainerH(x, y + height);
	drawContainerH(x + 40, y + height);
	drawContainerH(x + 80, y + height);
	drawContainerV8(x, y);
	drawContainerV8(x + length, y);
	drawContainerV8(x + length, y + 8);
	drawContainerV8(x, y + 16);
	drawContainerV8(x + length, y + 16);
}

void LevelManager::drawContainerRight(float x, float y, int length, int height)
{
	drawContainerH(x, y);
	drawContainerH(x + 40, y);
	drawContainerH(x + 80, y);
	drawContainerH(x, y + height);
	drawContainerH(x + 40, y + height);
	drawContainerH(x + 80, y + height);
	drawContainerV8(x, y);
	drawContainerV8(x + length, y);
	drawContainerV8(x, y + 8);
	drawContainerV8(x, y + 16);
	drawContainerV8(x + length, y + 16);
}
void LevelManager::drawContainerH(float x, float y) {
	new Obstacle(df::Vector(x+20, y), df::YELLOW, "container wall h");
}

void LevelManager::drawContainerHDown(float x, float y) {
	new Obstacle(df::Vector(x + 20, y), df::YELLOW, "container wall h down");
}

void LevelManager::drawContainerHUp(float x, float y) {
	new Obstacle(df::Vector(x + 20, y), df::YELLOW, "container wall h up");
}
void LevelManager::drawContainerV(float x, float y) {
	new Obstacle(df::Vector(x, y+6), df::YELLOW, "container wall v");
}

void LevelManager::drawContainerV8(float x, float y) {
	new Obstacle(df::Vector(x, y + 4), df::YELLOW, "v8");
}

void LevelManager::Level1() {
	//RM.loadMusic("sounds/calm-before-the-storm.wav", "calm");
	drawBarrier(20, 3);
	drawBarrier(20, 18);
	drawBarrier(100, 3);
	drawBarrier(100, 18);
	drawBarrier(120, 3);
	drawBarrier(120, 18);
	drawBox(55, 15);
	drawContainer(5, 3, 120, 24);
	p.setPosition(df::Vector(12, 22));
	new LevelEnd(df::Vector(123, 15),df::Vector(123, 19));
	//new HealthPack(df::Vector(30, 5));
	new Enemy(df::Vector(30, 21), false, horizontal);
	new Enemy(df::Vector(93, 9), true, horizontal);
	new Enemy(df::Vector(93, 15), false, vertical);
	new Enemy(df::Vector(112, 15), false, vertical);
}

void LevelManager::Level2() {
	//RM.loadMusic("sounds/calm-before-the-storm.wav", "calm");
	drawContainerDown(120, 3, 120, 24);
	drawContainerUp(120, 27, 120, 24);
	drawBarrier(130, 27);
	drawBarrier(130, 42);
	drawBarrier(130, 3);
	drawBarrier(130, 18);
	drawBarrier(130, 3);
	drawBarrier(130, 18);
	drawBarrier(145, 3);
	drawBarrier(145, 18);
	drawBarrier(210, 3);
	drawBarrier(210, 18);
	drawBarrier(225, 3);
	drawBarrier(225, 18);
	drawBarrier(225, 27);
	drawBarrier(225, 42);
	p.setPosition(df::Vector(123, 48));
	new HealthPack(df::Vector(124, 48));//df::Vector(235, 48));
	new Enemy(df::Vector(173, 25), false, horizontal);
	new Enemy(df::Vector(202, 25), true, horizontal);
	//new Enemy(df::Vector(138, 30), false , horizontal);
	//new Enemy(df::Vector(222, 30), true, horizontal);
	new Enemy(df::Vector(222, 34), true, horizontal);
	new Enemy(df::Vector(222, 44), true, horizontal);
	new Enemy(df::Vector(230, 15), true, horizontal);
	new Enemy(df::Vector(130, 15), false, horizontal);
	drawWideBox(181, 39);
	new Intel(df::Vector(125, 48));
	new Intel(df::Vector(235, 5));
	WM.setViewPosition(df::Vector(123, 48));
}

void generateLandmines() {
	new Landmine(df::Vector(130, 43));
	new Landmine(df::Vector(230, 33));
	new Landmine(df::Vector(125, 31));
	new Landmine(df::Vector(186, 43));
	new Landmine(df::Vector(208, 31));
	new Landmine(df::Vector(194, 45));
	new Landmine(df::Vector(217, 38));
	new Landmine(df::Vector(228, 43));
	new Landmine(df::Vector(140, 46));
	new Landmine(df::Vector(150, 40));
	new Landmine(df::Vector(170, 33));
	new Landmine(df::Vector(160, 38));
	new Landmine(df::Vector(165, 46));
}
void LevelManager::Level3() {
	p.setPosition(df::Vector(180, 15));
	drawContainerUpLeftRight(121, 27, 120, 24);
	drawContainerRight(1, 27, 120, 24);
	drawContainerLeft(241, 27, 120, 24);
	drawContainerDown(121, 3, 120, 24); 
	//TOP ROOM
	drawEntryBarrier(178.5, 12);
	new Enemy(df::Vector(152, 23), false, horizontal);
	new Enemy(df::Vector(208, 23), true, horizontal);
	drawBarrier(146, 18);
	drawBarrier(131, 18);
	drawBarrier(138.5, 3);
	drawBarrier(226, 18);
	drawBarrier(211, 18);
	drawBarrier(219.5, 3);
	new Enemy(df::Vector(222, 15), false, vertical);
	new Enemy(df::Vector(141, 15), false, vertical);
	new Intel(df::Vector(126, 23));
	new HealthPack(df::Vector(236, 23));
	//MIDDLE ROOM
	generateLandmines();
	//LEFT ROOM
	drawBox(34, 31.5);
	drawBox(89, 46.5);
	drawBox(34, 46.5);
	drawBox(89, 31.5);
	new Enemy(df::Vector(51, 32), false, horizontal);
	new Enemy(df::Vector(14, 36), false, vertical);
	new Enemy(df::Vector(51, 47), false, horizontal);
	new Enemy(df::Vector(108, 39), false, vertical);
	new Intel(df::Vector(63, 39));
	//RIGHT ROOM
	new Enemy(df::Vector(281, 36), true, vertical);
	new Enemy(df::Vector(291, 36), false, vertical);
	new Enemy(df::Vector(301, 36), true, vertical);
	new Enemy(df::Vector(311, 36), false, vertical);
	new Enemy(df::Vector(321, 36), true, vertical);
	new Enemy(df::Vector(331, 36), false, vertical);
	new Intel(df::Vector(358, 39));
	new Landmine(df::Vector(245, 35));
	new Landmine(df::Vector(245, 43));
	new Landmine(df::Vector(357, 35));
	new Landmine(df::Vector(357, 43));

}






//box is x 14 y 7
//barrier is x 5 y 9