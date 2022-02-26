#include "EventFOV.h"

EventFOV::EventFOV(df::Vector pos) {
	setPlayerPos(pos);
	setType(FOV_EVENT);
}

void EventFOV::setPlayerPos(df::Vector pos) {
	player_pos = pos;
}
df::Vector EventFOV::getPlayerPos() {
	return player_pos;
}