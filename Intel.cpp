#include "Intel.h"
#include "Vector.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "Player.h"
#include "LevelManager.h"
#include "LevelEnd.h"
Intel::Intel() {
	Intel(df::Vector(30, 5));
}
Intel::Intel(df::Vector pos) {
	setType("Intel");
	setSprite("intel");
	setSolidness(df::SOFT);
	setAltitude(3);
	setPosition(pos);
	active = true;
}
int Intel::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		bool player = ((p_collision_event->getObject1()->getType() == "Player") || (p_collision_event->getObject2()->getType() == "Player"));
		bool intel = ((p_collision_event->getObject1()->getType() == "Intel") || (p_collision_event->getObject2()->getType() == "Intel"));
		if (intel && player && active) {
			if (p.getIntel() == 1) {
				if (levelM.getLevelIndex() == 1) {
					new LevelEnd(df::Vector(180, 15), df::Vector(10, 15));
					p.setIntel(0);
				}
			}
			if (p.getIntel() == 3) {
				if (levelM.getLevelIndex() == 2) {
					new LevelEnd(df::Vector(180, 39), df::Vector(10, 15));
				}
			}
			p.setIntel(p.getIntel() + 1);
			active = false;
			if ((p_collision_event->getObject1()->getType() == "Intel")) {
				WM.markForDelete(p_collision_event->getObject1());
			}
			else {
				WM.markForDelete(p_collision_event->getObject2());
			}
		}
		return 1;
	}
}
