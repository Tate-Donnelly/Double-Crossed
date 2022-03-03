#include "Landmine.h"
#include "Vector.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "LMExplosion.h"
#include "EventHit.h"
#include "Sound.h"
#include <ResourceManager.h>
Landmine::Landmine() {
	Landmine(df::Vector(30, 5));
}
Landmine::Landmine(df::Vector pos) {
	setType("Landmine");
	setSprite("landmine");
	setSolidness(df::SOFT);
	setAltitude(3);
	setPosition(pos);
	active = true;
}
int Landmine::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		bool player = ((p_collision_event->getObject1()->getType() == "Player") || (p_collision_event->getObject2()->getType() == "Player"));
		bool landmine = ((p_collision_event->getObject1()->getType() == "Landmine") || (p_collision_event->getObject2()->getType() == "Landmine"));

		if (landmine && player && active) {
			active = false;
			if ((p_collision_event->getObject1()->getType() == "Landmine")) {
				EventHit ev;
				WM.onEvent(&ev);
				WM.markForDelete(p_collision_event->getObject1());
				LMExplosion* explosion = new LMExplosion;
				explosion->setPosition(this->getPosition());
				df::Sound* p_sound = RM.getSound("boom");
				p_sound->play(false);
			}
			else {
				EventHit ev;
				WM.onEvent(&ev);
				WM.markForDelete(p_collision_event->getObject2());
				LMExplosion* explosion = new LMExplosion;
				explosion->setPosition(this->getPosition());
				df::Sound* p_sound = RM.getSound("boom");
				p_sound->play(false);
			}
		}
		return 1;
	}
}