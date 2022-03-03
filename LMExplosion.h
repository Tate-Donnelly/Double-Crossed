#include "Object.h"

class LMExplosion : public df::Object {

private:
    int time_to_live;
    void step();

public:
    LMExplosion();
    int eventHandler(const df::Event* p_e) override;
};

