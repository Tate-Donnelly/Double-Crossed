#pragma once
#include <Object.h>
class Obstacle :
    public df::Object
{
public:
    Obstacle();
    Obstacle(df::Vector pos,df::Color color, std::string sprite);

   
};

