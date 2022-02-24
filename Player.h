#include "Object.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
class Player :
    public df::Object
    {
    private:
        int bullets;
        int lives;
        int move_countdown;
        int move_slowdown;
        int fire_countdown;
        int fire_slowdown;
        //Moves Player
        void move(int x, int y);
        //Player shoots bullet
        int shoot(const df::EventMouse* mouse);
        //Keyboard event
        int keyboard(const df::EventKeyboard* key);
        //Mouse event
        int mouse(const df::EventMouse* mouse);
    public:
        Player();
        ~Player();
        int eventHandler(const df::Event* p_e);
    };

