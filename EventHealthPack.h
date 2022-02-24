#pragma once
#include <Event.h>
const std::string HP_EVENT = "df::hp";
class EventHealthPack :
    public df::Event
{
public:
    EventHealthPack();
};

