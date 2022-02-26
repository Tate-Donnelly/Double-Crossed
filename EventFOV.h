#pragma once
#include <Event.h>
#include "Vector.h"
const std::string FOV_EVENT = "df::fov";
class EventFOV :
    public df::Event
{
private:
    df::Vector player_pos;
public:
    EventFOV(df::Vector pos);
    void setPlayerPos(df::Vector pos);
    df::Vector getPlayerPos();
};


