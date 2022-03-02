#include "Obstacle.h"
#include "LogManager.h"
Obstacle::Obstacle() {
	Obstacle(df::Vector(),df::Color::YELLOW, "one char wall h");
}
Obstacle::Obstacle(df::Vector pos,df::Color color, std::string sprite) {
	setSprite(sprite);
	getAnimation().getSprite()->setColor(color);
	setPosition(pos);
	setSolidness(df::HARD);
	setAltitude(3);
	setType("Obstacle");
	LM.writeLog("Obstacle Created");
}
