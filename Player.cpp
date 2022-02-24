#include "Player.h"
#include "Bullet.h"
#include "Reticle.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Event.h"
#include "EventHit.h"
#include "EventOut.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventHealthPack.h"
#include "EventView.h"
#include "ViewObject.h"
#pragma comment(lib, "proj2-Donnelly.lib")

Player::Player() {
	new Reticle;
	setType("Player");
	setAltitude(3);
	setSolidness(df::HARD);
	setSprite("playerL");

	setSpeed(1);
	setPosition(df::Vector(50,5));

	move_slowdown = 2;
	move_countdown = move_slowdown;

	bullets = 3;
	lives = 3;

	//Displays available bullets
	df::ViewObject* p_vo = new df::ViewObject;
	p_vo->setLocation(df::TOP_RIGHT);
	p_vo->setViewString("Bullets");
	p_vo->setValue(3);
	LM.writeLog("%d", p_vo->getValue());
	p_vo->setDrawValue(true);
	p_vo->setColor(df::YELLOW);


	//Displays lives
	df::ViewObject* p_vo2 = new df::ViewObject;
	p_vo2->setLocation(df::TOP_LEFT);
	p_vo2->setViewString("Lives");
	p_vo2->setValue(3);
	p_vo2->setDrawValue(true);
	p_vo2->setColor(df::YELLOW);
}
Player::~Player() {
	GM.setGameOver(true);
}

//Handles events
	//Returns 0 when ignored
int Player::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {//testObject moves to the cursor when clicked
		df::EventKeyboard* key = (df::EventKeyboard*)p_e;
		keyboard(key);
		return 1;
	}if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <df::EventMouse const*> (p_e);
		mouse(p_mouse_event);
		
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		return 1;
	}
	if (p_e->getType() == HIT_EVENT) {
		df::EventView* ev = new df::EventView("Lives", -1, true);
		WM.onEvent(ev);
		return 1;
	}
	if (p_e->getType() == HP_EVENT) {
		df::EventView* ev = new df::EventView("Lives", 1, true);
		WM.onEvent(ev);
		return 1;
	}
	return 0;
}

//Moves Player up and down
void Player::move(int x, int y) {
	if (move_countdown < 0) {
		return;
	}
	move_countdown = move_slowdown;
	//Move if in window

	df::Vector new_pos(getPosition().getX() + x, getPosition().getY() + y);
	WM.moveObject(this, new_pos);
	LM.writeLog("Old Position (%f,%f), New Position (%f,%f)", getPosition().getX(), getPosition().getY(), new_pos.getX(), new_pos.getY());
}

//Keyboard event
int Player::keyboard(const df::EventKeyboard* key) {
	switch (key->getKey()) {
	case df::Keyboard::Q:			// quit
		if (key->getKeyboardAction() == df::KEY_PRESSED)
			GM.setGameOver();
			WM.markForDelete(this);
		return 1;
	case df::Keyboard::W:       // up
		if (key->getKeyboardAction() == df::KEY_DOWN)
			LM.writeLog(0, "Up");
		move(0, -1);
		return 1;
	case df::Keyboard::S:       // down
		if (key->getKeyboardAction() == df::KEY_DOWN)
			LM.writeLog(0, "Down");
		move(0, +1);
		return 1;
	case df::Keyboard::A:       // left
		if (key->getKeyboardAction() == df::KEY_DOWN)
			LM.writeLog(0, "Left");
		setSprite("playerL");
		move(-1, 0);
		return 1;
	case df::Keyboard::D:       // right
		if (key->getKeyboardAction() == df::KEY_DOWN)
			LM.writeLog(0, "Right");
		setSprite("playerR");
		move(+1, 0);
		return 1;
	default: // Key not handled.
		return 0;
	};
	return 0;
}
//Mouse event
int Player::mouse(const df::EventMouse* mouse) {
	if (mouse->getMouseAction() == df::EventMouseAction::PRESSED) {
		if (mouse->getMouseButton() == df::Mouse::LEFT) {
			return shoot(mouse);
		}
		else {
			//Sneak Attack
			return 0;
		}
	}
	else if (mouse->getMouseButton() == df::Mouse::RIGHT) {
		return 1;
	}
	return 0;
}

//Player shoots bullet
int Player::shoot(const df::EventMouse* mouse) {
	//Time to fire
	if (fire_countdown > 0) {
		return 0;
	}
	fire_countdown = fire_slowdown;

	if (bullets > 0) {
		bullets--;
		df::EventView* ev=new df::EventView("Bullets", -1, true);
		WM.onEvent(ev);

		//Fire sound
		df::Sound* p_sound = RM.getSound("fire");
		p_sound->play(false);
		df::Vector pos = mouse->getMousePosition();
		// Compute normalized vector to position, then scale by speed 
		df::Vector v(pos.getX() - getPosition().getX(), pos.getY() - getPosition().getY());
		v.normalize();
		v.scale(1);
		Bullet* p = new Bullet(getPosition(), getId());
		p->setVelocity(v);
		return 1;
	}
	return 0;
}