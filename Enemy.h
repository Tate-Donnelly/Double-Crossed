#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"
class Enemy :
    public df::Object
{
private:
    int bullets;
    int fire_countdown;
    int fire_slowdown;
    bool facingLeft;
    //Moves Enemy
    void move(int x, int y);
    //Enemy shoots bullet
    int shoot();
public:
    Enemy(df::Vector position, bool direction);
    Enemy();
    ~Enemy();
    int eventHandler(const df::Event* p_e);
};

#endif //__ENEMY_H__
