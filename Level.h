#pragma once
#include "Object.h"
#include "ObjectList.h"
#include "Obstacle.h"
class Level :
    public df::Object
{
private:
    int  maxObstacles=50;
    df::ObjectList m_obstacles;
    int m_obstacle_count;
public:
    Level();
    void drawMap();
    int insertObstacle(Obstacle *o);
    int removeObstacle(Obstacle* o);
};

