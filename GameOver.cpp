#include "GameOver.h"
#include "GameStart.h"
#include "EventStep.h"
#include "EventView.h"
#include "Event.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

GameOver::GameOver() {
    setType("GameOver");
    //links to the "game over" sprite
    if (setSprite("gameover") == 0) {
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    }
    else {
        time_to_live = 0;
    }
    setColor(df::YELLOW);
    //Sets location
    setLocation(df::CENTER_CENTER);
    //Plays game over sound
    df::Sound* p_sound = RM.getSound("game over");
    p_sound->play(true);
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
    df::ObjectList object_list = WM.getAllObjects();
    df::ObjectListIterator i(&object_list);
    for (i.first(); !i.isDone(); i.next()) {
        df::Object* p_o = i.currentObject();
        if (p_o->getType() == "Enemy" || p_o->getType() == "ViewObject") {
            WM.markForDelete(p_o);
        }
        if (p_o->getType() == "GameStart") {
            dynamic_cast <GameStart*> (p_o)->playMusic();
            setColor(df::BLACK);
        }
    }
}

//Draws game over screen
int GameOver::draw() {
    return df::Object::draw();
}