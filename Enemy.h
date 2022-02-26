#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"
#include "FOV.h"
#include "Vector.h"

class FOV;

class Enemy :
    public df::Object
{
private:
    int bullets;
    int move_countdown;
    int move_slowdown;
    int fire_countdown;
    int fire_slowdown;
    float d_x;
    float d_y;
    int right_x; // for truncation purposes
    int right_y;
    int left_x;
    int left_y;
    int top_x;
    int top_y;
    int bot_x;
    int bot_y;
    bool facingLeft;
    FOV* myFOV;
    df::Vector FOVector;
    //df::Vector top;
    //df::Vector bottom;
    //df::Vector left;
    //df::Vector right;
    //Moves Enemy
    void move(float x, float y);
public:
    Enemy(df::Vector position, bool direction);
    Enemy();
    ~Enemy();
    int eventHandler(const df::Event* p_e);
    //Enemy shoots bullet
    int shoot();
    void step();
    void setFOV(FOV* fov);
    FOV* getFOV();
};

#endif //__ENEMY_H__
