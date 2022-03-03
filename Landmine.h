#pragma once
#include <Object.h>
class Landmine :
    public df::Object
{
private:
    bool active;
public:
    Landmine();
    Landmine(df::Vector pos);
    int eventHandler(const df::Event* p_e) override;
};
