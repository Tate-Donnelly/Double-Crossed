#pragma once
#include <Object.h>
class HealthPack :
    public df::Object
{
private:
    bool active;
public:
    HealthPack();
    HealthPack(df::Vector pos);
    int eventHandler(const df::Event* p_e) override;
};

