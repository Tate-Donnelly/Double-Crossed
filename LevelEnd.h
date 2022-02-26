#pragma once
#include <Object.h>
#include "Event.h"
class LevelEnd :
    public df::Object
{
private:
    bool active;//Goes to false when Player touches it to avoid jumping multiple levels
public:
    LevelEnd(df::Vector pos);
    ~LevelEnd();
    int eventHandler(const df::Event* p_e);
};

