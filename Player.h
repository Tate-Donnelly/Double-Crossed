#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Object.h"
#include "Enemy.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
class Player :
    public df::Object
    {
    private:
        int bullets;
        int lives;
        int delta_bullets;
        int delta_lives;
        int move_countdown;
        int move_slowdown;
        int fire_countdown;
        int fire_slowdown;
        bool active;
        bool sneakAttack;
        Object *target;
        //Moves Player
        void move(int x, int y);
        //Player shoots bullet
        int shoot(const df::EventMouse* mouse);
        //Keyboard event
        int keyboard(const df::EventKeyboard* key);
        //Mouse event
        int mouse(const df::EventMouse* mouse);
    public:
        Player(df::Vector position);
        Player();
        ~Player();
        int eventHandler(const df::Event* p_e);
        //If level is reset values are reset
        void valueReset();
        //Sets deltas to 0
        void resetDeltas();
        void setActive(bool isActive=true);
    };
#endif

