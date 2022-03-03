#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__
#include <Manager.h>
#include "Player.h"
#include "Music.h"
#include "Event.h"
#include "ObjectList.h"

# define levelM LevelManager :: getInstance ()
class LevelManager :
    public df::Manager
{
private:
    int totalLevels=3;
    int level_index;
    df::ObjectList m_protectedObjects;//Objects that should not be deleted when level changes
    
public:
    LevelManager();
    //Get the instance of the LevelManager
    static LevelManager& getInstance();

    int startUp();
    void shutDown();

    //Load given level
    //Return 1 if error, else 0
    int loadLevel(int levelID);

    //Getter/Setter for level_index
    void setLevelIndex(int level);
    int getLevelIndex() const;


    //Insert an object that will be protected from loadlevel
    void insertProtected(df::Object* object);

    //Loads the next level
    //If there are no more levels return 1, else 0
    int nextLevel();

    //Reset the current level
    void resetLevel();

    void drawContainer(float x, float y, int length, int height);
    void drawContainerDown(float x, float y, int length, int height);
    void drawContainerUp(float x, float y, int length, int height);

    void drawContainerH(float x, float y);
    void drawContainerHDown(float x, float y);
    void drawContainerHUp(float x, float y);

    void drawContainerV(float x, float y);

    void drawBarrier(float x, float y);

    void drawBox(float x, float y);

    void drawWideBox(float x, float y);

    void Level1();
    void Level2();
};
#endif

