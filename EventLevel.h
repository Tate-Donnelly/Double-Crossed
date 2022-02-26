#pragma once
#include <Event.h>
const std::string LEVEL_EVENT = "df::level";
class EventLevel :
    public df::Event
{
public:
    EventLevel();
};

