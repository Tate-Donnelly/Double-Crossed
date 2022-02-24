#include "EventCollision.h"
#include "Object.h"
#include <string.h>

class Bullet : public df::Object {

private:
    int fromID;
    void out();
    void hit(const df::EventCollision* p_collision_event);

public:
    Bullet(df::Vector pos, int id);
    int eventHandler(const df::Event* p_e) override;
    //Get/Set ID that fired bullet
    void setFromID(int id);
    int getID() const;
};