#include "GameOver.h"
#include "GameStart.h"
#include "EventStep.h"
#include "EventView.h"
#include "Event.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "LevelManager.h"
#include "Player.h"

GameOver::GameOver() {
    //p.setPosition(df::Vector(40, 12));
    p.getAnimation().getSprite()->setColor(df::BLACK);
    setAltitude(3);
    setType("GameOver");
    //links to the "game over" sprite
    printf("gameOver constructor");
;    if (setSprite("gameover") == 0) {
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    }
    else {
        time_to_live = 0;
    }
    setColor(df::YELLOW);
    //Sets location
    df::Vector pos(p.getPosition());
    setPosition(pos);
    printf("inserting into levelmanager");
    levelM.insertProtected(this);
    printf("inserted into levelmanager");
}

//Handles event
int GameOver::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    return 0;//Ignore
}

//Message count down
void GameOver::step() {
    time_to_live--;
    if (time_to_live <= 0) {
        WM.markForDelete(this);
    }
}

//Resets game for Game Start
GameOver::~GameOver() {
    //Removes Enemies and ViewObjects
    df::ObjectListIterator i(new df::ObjectList(WM.getAllObjects()));
    for (i.first(); !i.isDone(); i.next()) {
        df::Object* p_o = i.currentObject();
        if (p_o->getType() != "Player" && p_o->getType() != "Reticle" && p_o->getType() != "GameOver") {
            std::cout << p_o->getType() << "\n";
            WM.markForDelete(p_o);
            
        }
        
    }
    exit(0);
}

//Draws game over screen
int GameOver::draw() {
    return df::Object::draw();
}