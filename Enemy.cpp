#include "Enemy.h"
#include "WorldManager.h"
#include "Event.h"
#include "EventHit.h"
#include "EventFOV.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Vector.h"
#include "Sound.h"
#include "EventStep.h"
#include "Bullet.h"

Enemy::Enemy()
{
	Enemy(df::Vector(70, 40), true);
}

Enemy::Enemy(df::Vector position, bool direction)
{
	setType("Enemy");
	setAltitude(3);
	setSolidness(df::HARD);
	setSpeed(1);
	move_slowdown = 100;
	move_countdown;
	fire_slowdown = 100;
	fire_countdown;
	setPosition(position);
	/*
	right = position;
	left = df::Vector(position.getX() - 20, position.getY());
	bottom = df::Vector(position.getX() - 10, position.getY() + 10);
	top = df::Vector(position.getX() - 10, position.getY() - 10);
	printf("Vector: x = %f, y = %f", position.getX(), position.getY());
	*/
	right_x = position.getX();
	right_y = position.getY();
	left_x = right_x - 20;
	left_y = right_y;
	top_x = right_x - 10;
	top_y = right_y - 10;
	bot_x = top_x;
	bot_y = right_y + 10;
	fire_countdown = 5;
	fire_slowdown;
	facingLeft = direction;
	if (facingLeft) {
		setSprite("enemyL");
		LM.writeLog("the sprite loaded");
	}
	else {
		setSprite("enemyR");
		LM.writeLog("the sprite loaded");
	}
	d_x = 0;
	d_y = 0;
}

Enemy::~Enemy()
{

}

int Enemy::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == HIT_EVENT) {
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;

}

void Enemy::move(float x, float y)
{
	df::Vector v = getPosition();
	int a = v.getX(); //The reason this is here is to truncate the values for comparison
	int b = v.getY();
	//Move if in window
	if ((a == right_x) && (b == right_y)) {
		d_x = -0.1;
		d_y = 0.1;
		setSprite("enemyL");
		facingLeft = true;
	}
	if ((a == bot_x) && (b == bot_y)) {
		d_x = -0.1;
		d_y = -0.1;
	}
	if ((a == left_x) && (b == left_y)) {
		d_x = 0.1;
		d_y = -0.1;
		setSprite("enemyR");
		facingLeft = false;
	}
	if ((a == top_x) && (b == top_y)) {
		d_x = 0.1;
		d_y = 0.1;
	}
	df::Vector new_pos(getPosition().getX() + d_x, getPosition().getY() + d_y);
	df::Vector new_pos2;
	if (facingLeft) {
		new_pos2 = df::Vector(getPosition().getX() + d_x - 3, getPosition().getY() + d_y);
	}
	else {
		new_pos2 = df::Vector (getPosition().getX() + d_x + 10, getPosition().getY() + d_y);
	}
	setVelocity(new_pos);
	WM.moveObject(this, new_pos);
	WM.moveObject(myFOV, new_pos2);
	LM.writeLog("Enemy: Old Position (%f,%f), New Position (%f,%f)", getPosition().getX(), getPosition().getY(), new_pos.getX(), new_pos.getY());
}

int Enemy::shoot()
{
	//Fire sound
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play(false);
	// Compute normalized vector to position, then scale by speed 
	// Fire Bullet towards target.
	df::Vector v = getPosition();
	printf("Vector: x = %f, y = %f", v.getX(), v.getY());
	v.setY(0);
	if (facingLeft) {
		v.setX(0 - v.getX());
	}
	else {
		v.setX(100 - v.getX()); //figure out level boundary length to make it fire to the maximum
	}
	v.normalize();
	v.scale(1);
	Bullet* p = new Bullet(df::Vector(getPosition().getX(), getPosition().getY() - 1.25), getId());
	p->setVelocity(v);
	return 1;
}

void Enemy::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;
	if (move_countdown == 0) {
		move(-0.1, 0);
		getFOV()->move(-0.1, 0);
	}
	// NOTE - in step()
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

void Enemy::setFOV(FOV* fov)
{
	myFOV = fov;
}

FOV* Enemy::getFOV()
{
	return myFOV;
}
