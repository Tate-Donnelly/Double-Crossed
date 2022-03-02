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
	Enemy(df::Vector(70, 40), true, horizontal);
}

Enemy::Enemy(df::Vector position, bool direction, MovementPatern mp)
{
	setType("Enemy");
	setAltitude(3);
	setSolidness(df::HARD);
	setSpeed(1);
	bounce = false;
	move_slowdown = 100;
	move_countdown;
	fire_slowdown = 100;
	fire_countdown;
	setPosition(position);
	setMovement(mp);
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
	myFOV = new FOV(this);
}

Enemy::~Enemy()
{
	WM.markForDelete(myFOV);
}

int Enemy::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		bool enemy = ((p_collision_event->getObject1()->getType() == "Enemy") || (p_collision_event->getObject2()->getType() == "Enemy"));
		bool enemy2 = ((p_collision_event->getObject1()->getType() == "Enemy") && p_collision_event->getObject1() != this) || ((p_collision_event->getObject2()->getType() == "Enemy") && p_collision_event->getObject2() != this);
		bool obstacle = ((p_collision_event->getObject1()->getType() == "Obstacle") || (p_collision_event->getObject2()->getType() == "Obstacle"));
		if (enemy && (obstacle || enemy2)  && bounce) {
			LM.writeLog(0, "Obstacle Found");
			myFOV->setObstacleCollision(false);
			facingLeft = !facingLeft;
		}

	}
	return 0;

}

void Enemy::move()
{
	switch (getMovement()) {
	case horizontal:
		bounce = true;
		movementHorizontal();
		break;
	case vertical:
		bounce = true;
		movementVertical();
		break;
		//case diamond:
			//movementDiamond();
			//break;
	case hugObstacle:
		movementHugObstacle();
		break;
	case square:
		moveSquare();
		break;
	}
}

int Enemy::shoot()
{
	//Time to fire
	if (fire_countdown > 0) {
		return 1;
	}
	fire_countdown = fire_slowdown;
	//Fire sound
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play(false);
	df::Vector v = getPosition();
	v.setY(0);
	if (facingLeft) {
		v.setX(0 - v.getX());
	}
	else {
		v.setX(100 - v.getX()); //figure out level boundary length to make it fire to the maximum
	}
	v.normalize();
	v.scale(1);
	Bullet* pos = new Bullet(getPosition(), getId());
	pos->setVelocity(v);

	return 1;
}

void Enemy::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;
	if (move_countdown == 0) {
		move();
		//getFOV()->move(-.5, 0);
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

bool Enemy::CanBounce() const
{
	return bounce;
}

void Enemy::setMovement(MovementPatern mp) {
	movementPattern = mp;
}
MovementPatern Enemy::getMovement() const {
	return movementPattern;
}
void Enemy::movementBackAndForth() {
	bounce = true;
	float x = getPosition().getX();
	float y = getPosition().getY();
	setVelocity(getDirection());
	df::Vector new_pos2;
	if (x < 11 && facingLeft == true) {
		x = 0;
		setSprite("enemyR");
		facingLeft = false;
	}
	if (x > 69 && facingLeft == false) {
		x = 80;
		setSprite("enemyL");
		facingLeft = true;
	}
	if (facingLeft) {
		d_x = -0.25;
		setPosition(df::Vector(x + d_x, y));
		new_pos2 = df::Vector(x + d_x - 6, y);
	}
	else {
		d_x = 0.25;
		setPosition(df::Vector(x + d_x, y));
		new_pos2 = df::Vector(x + d_x + 7, y);
	}
	WM.moveObject(this, getPosition());
	WM.moveObject(myFOV, new_pos2);
}

void Enemy::movementHorizontal() {
	if (facingLeft) {
		setSprite("enemyL");
		setVelocity(df::Vector(-.25, 0));
		if (!myFOV->getObstacleCollision()) {
			myFOV->setPosition(df::Vector(getPosition().getX() - 6, getPosition().getY()));
			myFOV->setVelocity(df::Vector(-0.25, 0));
		}
		else {
			//myFOV->setVelocity(df::Vector(0, 0));
			myFOV->setObstacleCollision(false);
			myFOV->setPosition(df::Vector(myFOV->getPosition().getX() + 1, getPosition().getY()));
			setSprite("enemyR");
			facingLeft = false;
			myFOV->setVelocity(df::Vector(0.25, 0));
		}
	}
	else {
		setSprite("enemyR");
		setVelocity(df::Vector(.25, 0));
		if (!myFOV->getObstacleCollision()) {
			myFOV->setPosition(df::Vector(getPosition().getX() + 7, getPosition().getY()));
			myFOV->setVelocity(df::Vector(.25, 0));
		}
		else {
			//myFOV->setVelocity(df::Vector(0, 0));
			myFOV->setObstacleCollision(false);
			myFOV->setPosition(df::Vector(myFOV->getPosition().getX() - 1, getPosition().getY()));
			setSprite("enemyL");
			facingLeft = true;
			myFOV->setVelocity(df::Vector(-0.25, 0));
		}
	}
}

void Enemy::movementVertical() {
	if (facingLeft) {
		setSprite("enemyL");
		setVelocity(df::Vector(0, -.15));
		if (!myFOV->getObstacleCollision()) {
			//myFOV->setPosition(df::Vector(getPosition().getX(), getPosition().getY()  3));
			myFOV->setVelocity(df::Vector(0, -.15));
		}
		else {
			myFOV->setVelocity(df::Vector(0, 0));
			myFOV->setPosition(df::Vector(getPosition().getX(), getPosition().getY() - 1));
		}
	}
	else {
		setSprite("enemyR");
		setVelocity(df::Vector(0, .15));
		if (!myFOV->getObstacleCollision()) {
			//myFOV->setPosition(df::Vector(getPosition().getX(), getPosition().getY() + 3));
			myFOV->setVelocity(df::Vector(0, .15));

		}
		else {
			myFOV->setVelocity(df::Vector(0, 0));
			myFOV->setPosition(df::Vector(getPosition().getX(), getPosition().getY() + 1));

		}
	}
}

void Enemy::moveSquare() {
	df::Vector v = getPosition();
	float a = v.getX(); //The reason this is here is to truncate the values for comparison
	float b = v.getY();
	//Move if in window
	if (a >= right_x && b >= bottom_y) { //bottom right
		d_x = -0.5;
		d_y = 0;
		setSprite("enemyL");
		facingLeft = true;
	}
	if (a <= left_x && b >= bottom_y) { //bottom left
		d_x = 0;
		d_y = -0.2;
	}
	if (a <= left_x && b <= top_y) {//top left
		d_x = 0.5;
		d_y = 0;
		setSprite("enemyR");
		facingLeft = false;
	}
	if (a >= right_x && b <= top_y) {//top right
		d_x = 0;
		d_y = 0.2;
	}
	df::Vector new_pos(getPosition().getX() + d_x, getPosition().getY() + d_y);
	df::Vector new_pos2;
	if (facingLeft) {
		new_pos2 = df::Vector(getPosition().getX() + d_x - 6, getPosition().getY() + d_y);
	}
	else {
		new_pos2 = df::Vector(getPosition().getX() + d_x + 7, getPosition().getY() + d_y);
	}
	setVelocity(new_pos);
	WM.moveObject(this, new_pos);
	WM.moveObject(myFOV, new_pos2);
	LM.writeLog(0, "Enemy: Old Position (%f,%f), New Position (%f,%f)", getPosition().getX(), getPosition().getY(), new_pos.getX(), new_pos.getY());
}

/*
void Enemy::movementDiamond() {
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
		new_pos2 = df::Vector(getPosition().getX() + d_x + 10, getPosition().getY() + d_y);
	}
	setVelocity(new_pos);
	WM.moveObject(this, new_pos);
	WM.moveObject(myFOV, new_pos2);
	LM.writeLog(0, "Enemy: Old Position (%f,%f), New Position (%f,%f)", getPosition().getX(), getPosition().getY(), new_pos.getX(), new_pos.getY());
}
*/
void Enemy::movementHugObstacle() {

}