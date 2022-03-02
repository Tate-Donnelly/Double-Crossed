#include "Bullet.h"
#include "Saucer.h"
#include "EventOut.h"
#include "EventHit.h"
#include "EventView.h"
#include "EventCollision.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

Bullet::Bullet(df::Vector pos, int id) {
    setSprite("bullet");//Links to bullet sprite
    setType("Bullet");//Bullet 
    setSolidness(df::SOFT);//Moves through Player
    //Sets the starting location
    df::Vector p(pos.getX(), pos.getY());
    setPosition(p);
    //Sets speed
    setSpeed(1);

    //Sets the ID that fired the bullet
    setFromID(id);
}

//Handles events
int Bullet::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        const df::EventOut* p_out_event = dynamic_cast <const df::EventOut*> (p_e);
        out();
        return 1;
    }if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
        hit(p_collision_event);
        return 1;
    }
    return 0;//Ignores Event
}

//Bullet is marked for deletion if it moves out of the window
void Bullet::out() {
    WM.markForDelete(this);
}

// If Bullet hits Enemy, mark Enemy and Bullet for deletion.
void Bullet::hit(const df::EventCollision* p_collision_event) {
    bool bullet = ((p_collision_event->getObject1()->getType() == "Bullet") || (p_collision_event->getObject2()->getType() == "Bullet"));
    bool enemy = ((p_collision_event->getObject1()->getType() == "Enemy") || (p_collision_event->getObject2()->getType() == "Enemy"));
    bool player = ((p_collision_event->getObject1()->getType() == "Player") || (p_collision_event->getObject2()->getType() == "Player"));
    bool obstacle = ((p_collision_event->getObject1()->getType() == "Obstacle") || (p_collision_event->getObject2()->getType() == "Obstacle"));
    if ((bullet && enemy)) {
        if ((fromID != p_collision_event->getObject1()->getId()) && (fromID != p_collision_event->getObject2()->getId())) {
            WM.markForDelete(p_collision_event->getObject1());
            WM.markForDelete(p_collision_event->getObject2());
        }
    }
    else if (bullet && obstacle) {
        if ((p_collision_event->getObject1()->getType() == "Bullet")) {
            WM.markForDelete(p_collision_event->getObject1());
        }
        else {
            WM.markForDelete(p_collision_event->getObject2());
        }
    }
    else if (bullet && player) {
        if ((fromID != p_collision_event->getObject1()->getId()) && (fromID != p_collision_event->getObject2()->getId())) {
            EventHit ev;
            WM.onEvent(&ev);
            if ((p_collision_event->getObject1()->getType() == "Bullet")) {
                WM.markForDelete(p_collision_event->getObject1());
            }
            else {
                WM.markForDelete(p_collision_event->getObject2());
            }
        }
    }
}

//Get/Set ID that fired bullet
void Bullet::setFromID(int id) {
    fromID = id;
}
int Bullet::getID() const {
    return fromID;
}