#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameStart.h"
#include "Player.h"
//function prototypes
void loadResources(void);
void populateWorld(void);

int main() {
    if (GM.startUp()) {
        LM.writeLog(10, "Error starting game manager!");
    }
    else {
        LM.setFlush(true);//Set flush of logfile during development

        WM.setBoundary(df::Box(df::Vector(0, 0), 240, 30));
        WM.setView(df::Box(df::Vector(0, 0), 80, 24));
        WM.setViewPosition(df::Vector(40, 12));
        p.setPosition(df::Vector(40, 12));
        p.setSprite("");

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
    RM.loadSprite("sprites/LevelEnd.txt", "LevelEnd");
    RM.loadSprite("sprites/one-char-wall-h-spr.txt", "one char wall h");
    RM.loadSprite("sprites/one-char-wall-v-spr.txt", "one char wall v");
    RM.loadSprite("sprites/container-wall-h-spr.txt", "container wall h");
    RM.loadSprite("sprites/container-wall-v-spr.txt", "container wall v");
    RM.loadSprite("sprites/box-spr.txt", "box");
    RM.loadSprite("sprites/container-barrier-wall-h-spr.txt", "container barrier wall h");
    RM.loadSprite("sprites/container-barrier-wall-v-spr.txt", "container barrier wall v");
    RM.loadSprite("sprites/fov-spr.txt", "fov");
    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/game-over.wav", "game over");
    RM.loadMusic("sounds/chase.wav", "chase");
    RM.getMusic("chase")->stop();
    RM.loadMusic("sounds/city.wav", "city");
    RM.getMusic("city")->stop();
    RM.loadMusic("sounds/documentary.wav", "documentary");
    RM.getMusic("documentary")->stop();
    RM.loadMusic("sounds/tense.wav", "tense");
    RM.getMusic("tense")->stop();
  //  RM.loadSprite("sprites/fov-q1-spr.txt", "q1");
}

//Populate the world with sprites and sounds
void populateWorld() {
    GameStart* g=new GameStart();
    
}