#include "LevelEnd.h"
#include "LevelManager.h"
#include "WorldManager.h"
#include "EventCollision.h"
#include "EventView.h"
#include "EventLevel.h"

LevelEnd::LevelEnd(df::Vector pos, df::Vector next_player_pos) {
	setType("LevelEnd");
	setSprite("LevelEnd");
	setSolidness(df::SOFT);
	setAltitude(3);
	setPosition(pos);
	player_pos = next_player_pos;
	active = true;
}
LevelEnd::~LevelEnd() {

}
int LevelEnd::eventHandler(const df::Event* p_e) {
	if (p_e->getType()==df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		if (active && ((p_collision_event->getObject1()->getType() == "Player") || (p_collision_event->getObject2()->getType() == "Player"))){
			active = false;
			if (1 != levelM.nextLevel()) {
				p.setPosition(player_pos);
				//p.setActive(false);
				df::EventView ev("Level", 1, true);
				WM.onEvent(&ev);
			}
		}
		return 1;
	}
	return 0;
}