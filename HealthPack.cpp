#include "HealthPack.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventHealthPack.h"
#include "WorldManager.h"
HealthPack::HealthPack() {
	HealthPack(df::Vector(30,5));
}
HealthPack::HealthPack(df::Vector pos) {
	setType("HealthPack");
	setSprite("healthpack");
	setSolidness(df::SOFT);
	setAltitude(3);
	setPosition(pos);
	active = true;
}
int HealthPack::eventHandler(const df::Event* p_e){
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		bool player = ((p_collision_event->getObject1()->getType() == "Player") || (p_collision_event->getObject2()->getType() == "Player"));
		bool hp = ((p_collision_event->getObject1()->getType() == "HealthPack") || (p_collision_event->getObject2()->getType() == "HealthPack"));

		if (hp && player && active) {
			active = false;
			if ((p_collision_event->getObject1()->getType() == "HealthPack")) {
				WM.markForDelete(p_collision_event->getObject1());
			}
			else {
				WM.markForDelete(p_collision_event->getObject2());
			}
			WM.onEvent(new EventHealthPack);
		}
		return 1;
	}
}