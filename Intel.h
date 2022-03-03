#pragma once
#include <Object.h>
class Intel :
    public df::Object
{
private:
    bool active;
public:
    Intel();
    Intel(df::Vector pos);
    int eventHandler(const df::Event* p_e) override;
};

