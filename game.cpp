#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameStart.h"

//function prototypes
void loadResources(void);
void populateWorld(void);

int main() {
    if (GM.startUp()) {
        LM.writeLog(10, "Error starting game manager!");
    }
    else {
        LM.setFlush(true);//Set flush of logfile during development

        loadResources();//Loads the game's resources
        populateWorld();//Populate game world with some objects.
        
        
        GM.run();
        GM.shutDown();
    }
	return 0;
}
//Load resources
void loadResources(void) {
    RM.loadSprite("sprites/player-left-spr.txt", "playerL");
    RM.loadSprite("sprites/player-right-spr.txt", "playerR");
    RM.loadSprite("sprites/enemy-left-spr.txt", "enemyL");
    RM.loadSprite("sprites/enemy-right-spr.txt", "enemyR");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("sprites/healthpack-spr.txt", "healthpack");
}

//Populate the world with sprites and sounds
void populateWorld() {
    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/game-over.wav", "game over");
    RM.loadMusic("sounds/start-music.wav", "start music");
    RM.getMusic("start music")->stop();
    new GameStart();
}