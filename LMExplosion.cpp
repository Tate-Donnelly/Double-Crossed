#include "LMExplosion.h"
#include <Object.h>
#include <DisplayManager.h>
#include <EventStep.h>
#include <WorldManager.h>

LMExplosion::LMExplosion() {
	setSolidness(df::SPECTRAL);
	// Link to "explosion" sprite.
	if (setSprite("landmine explosion") == 0)
		// Set live time as long as sprite length.
		time_to_live = getAnimation().getSprite()->getFrameCount();
	else
		time_to_live = 0;
}

void LMExplosion::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

int LMExplosion::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	// If get here, have ignored this event.
	return 0;
}
