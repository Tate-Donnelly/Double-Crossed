#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"
#include "FOV.h"
#include "Player.h"

class FOV;
enum MovementPatern {
    backAndForth,
    diamond,
    hugObstacle,
    square
};

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
    float left_x;
    float bottom_y;
    float right_x;
    float top_y;
    bool facingLeft;
    FOV* myFOV;
    df::Vector FOVector;
    MovementPatern movementPattern;
    //df::Vector top;
    //df::Vector bottom;
    //df::Vector left;
    //df::Vector right;
    //Moves Enemy
    void move();
    bool canShoot;
    bool bounce;
public:
    Enemy(df::Vector position, bool direction, MovementPatern mp);
    Enemy();
    ~Enemy();
    int eventHandler(const df::Event* p_e);
    //Enemy shoots bullet
    int shoot();
    void step();
    void setFOV(FOV* fov);
    FOV* getFOV();
    void setCanShoot(bool shoot = true);
    bool CanShoot() const;
    void setMovement(MovementPatern mp);
    MovementPatern getMovement() const;
    void movementBackAndForth();
    void moveSquare();
    void movementDiamond();
    void movementHugObstacle();
};

#endif //__ENEMY_H__