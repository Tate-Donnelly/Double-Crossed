#ifndef __FOV_H__
#define __FOV_H__

#include "Object.h"
#include "Vector.h"
#include "Enemy.h"

class Enemy;

class FOV : public df::Object {
public: 
	Enemy* myEnemy;
	FOV(df::Vector e_pos, Enemy* ene);
	FOV();
	~FOV();
	int eventHandler(const df::Event* p_e);
	void move(float x, float y);
	//float getVisionX();
	//void setVisionX(float new_vision_x);
	//float getVisionY();
	//void setVisionY(float new_vision_y);
private:
	//float vision_x;
	//float vision_y;
};

#endif // __FOV_H__
