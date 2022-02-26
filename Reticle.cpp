#include "Reticle.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LevelManager.h"

Reticle::Reticle() {
    levelM.insertProtected(this);
    setType("Reticle");
    setSolidness(df::SPECTRAL);
    setAltitude(3);
    df::Vector p(WM.getBoundary().getHorizontal() / 2,
        WM.getBoundary().getVertical() / 2);
    setPosition(p);
}

//Handles events
int Reticle::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            //Moves with cursor
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }
    }
    return 0;//Ignore event
}
//Draws the reticle on the window
int Reticle::draw() {
    return DM.drawCh(getPosition(), RETICLE_CHAR, df::WHITE);
}

