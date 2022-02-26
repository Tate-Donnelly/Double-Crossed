#pragma once
#include <Event.h>
const std::string START_EVENT = "df::start";
class EventStart :
    public df::Event
{
    EventStart();
};

