#pragma once
#include <Event.h>
const std::string HIT_EVENT = "df::hit";
class EventHit :
    public df::Event
{
public:
    EventHit();
};

