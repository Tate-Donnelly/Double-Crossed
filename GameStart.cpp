#include "GameStart.h"
#include "GameOver.h"
#include "Color.h"
#include "EventKeyboard.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Music.h"
#include "Player.h"
#include "HealthPack.h"
#include <SFML/Graphics.hpp>

GameStart::GameStart() {
    LM.writeLog("GameStart");
    setType("GameStart");
    //Link to "message" sprite
    setSprite("gamestart");
    setSolidness(df::SPECTRAL);
    //Put in center of screen
    df::Vector pos(40, 12);
    setPosition(pos);
    //Plays start music
    p_music = RM.getMusic("tense");
    playMusic();
    
    levelM.insertProtected(this);
}

//Play start music
void GameStart::playMusic() {
    p_music->play();
}

//Starts the game
void GameStart::start() {
    levelM.startUp();
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
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
                exit(0);
                //GM.setGameOver(true);
                //p.shutDown();
            }
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