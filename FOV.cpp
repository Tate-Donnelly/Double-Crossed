#include "FOV.h"
#include "EventFOV.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "LogManager.h"

FOV::FOV(Enemy* ene)
{
	setAltitude(3);
	myEnemy = ene;
	setType("FOV");
	if (ene->getMovement() == vertical) {
		setSprite("fov vertical");
	}
	else {
		setSprite("fov");
	}
	setSolidness(df::SOFT);
	if (ene->getMovement() == horizontal) {
		setPosition(ene->getPosition());
	}
	else {
		setPosition(df::Vector(ene->getPosition().getX(), ene->getPosition().getY() + 3));
	}
	obstacleCollision = false;
	collisionCount = 0;
}

FOV::FOV() {
	FOV(new Enemy);
}

int FOV::eventHandler(const df::Event* p_e) {
	if ((p_e->getType() == df::COLLISION_EVENT)) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		bool FOV = ((p_collision_event->getObject1()->getType() == "FOV") || (p_collision_event->getObject2()->getType() == "FOV"));
		bool dFOV = ((p_collision_event->getObject1()->getType() == "FOV") && (p_collision_event->getObject2()->getType() == "FOV"));
		bool player = ((p_collision_event->getObject1()->getType() == "Player") || (p_collision_event->getObject2()->getType() == "Player"));
		bool obstacle = ((p_collision_event->getObject1()->getType() == "Obstacle") || (p_collision_event->getObject2()->getType() == "Obstacle"));
		if ((FOV && player)) {
			if (p.getLives() > 0) {
				myEnemy->shoot();
				return 1;
			}
		}
		else if (dFOV) {
			LM.writeLog(0, "two FOVs collided");
			setObstacleCollision(true);
			setVelocity(df::Vector(0, 0));
			myEnemy->move();
		}
		else if (FOV && obstacle && ((myEnemy->getMovement() == horizontal) || (myEnemy->getMovement() == vertical))) {
			LM.writeLog(0, "FOV Found Obstacle");
			collisionCount++;
			if (collisionCount >= 4) {
				setObstacleCollision(true);
				setVelocity(df::Vector(0, 0));
				myEnemy->move();
				collisionCount = 0;
			}

		}
	}
	return 0;//Ignores Event
}

void FOV::setObstacleCollision(bool c)
{
	obstacleCollision = c;
}

bool FOV::getObstacleCollision() {
	return obstacleCollision;
}
void FOV::move(float x, float y)
{

}