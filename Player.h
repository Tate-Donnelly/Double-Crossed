#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Object.h"
#include "Enemy.h"
#include "EventMouse.h"
#include "EventKeyboard.h"

# define p Player :: getInstance ()

class Player :
    public df::Object
    {
    private:
        Player();
        Player(df::Vector position);
        ~Player();
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
        int intelCount;
        Object *target;
        //Moves Player
        void move(float x, float y);
        //Player shoots bullet
        int shoot(const df::EventMouse* mouse);
        //Keyboard event
        int keyboard(const df::EventKeyboard* key);
        //Mouse event
        int mouse(const df::EventMouse* mouse);
    public: 
        void start();
        void shutDown();
        static Player& getInstance();
        int eventHandler(const df::Event* p_e);
        //If level is reset values are reset
        void valueReset();
        //Sets deltas to 0
        void resetDeltas();
        void setActive(bool isActive=true);
        void setIntel(int ic);
        int getIntel();
        int getLives();
    };
#endif

