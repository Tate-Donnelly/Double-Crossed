#include "GameStart.h"
#include "GameOver.h"
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Music.h"
#include "Player.h"
#include "HealthPack.h"

GameStart::GameStart() {
    setType("GameStart");
    //Link to "message" sprite
    setSprite("gamestart");
    setBox(df::Box(df::Vector(0,0), 80, 24));
    //Put in center of screen
    setLocation(df::CENTER_CENTER);

    df::Vector p(WM.getBoundary().getHorizontal() / 2,
        WM.getBoundary().getVertical() / 2);
    setPosition(p);

    setColor(df::YELLOW);
    //Plays start music
    p_music = RM.getMusic("start music");
    playMusic();
}

//Play start music
void GameStart::playMusic() {
    p_music->play();
}

//Starts the game
void GameStart::start() {
    new Player;
    new HealthPack(df::Vector(30, 5));
    p_music->pause();
    // When game starts, paint it black.
    getAnimation().getSprite()->setColor(df::BLACK);
}

//Handles events
int GameStart::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::Q:			// quit
            GM.setGameOver();
            break;
        case df::Keyboard::SPACE: 	//begin game
            if ((p_keyboard_event->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED) &&
                !(getAnimation().getSprite()->getColor()==df::BLACK)) {
                start();
            }
            break;
        default: // Key is not handled.
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

//Override default draw so as not to display "value"
int GameStart::draw() {
    return df::Object::draw();
}