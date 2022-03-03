#pragma once
#include <ViewObject.h>
#include "Music.h"
class GameStart :
    public df::Object
{

private:
    df::Music* p_music;
    void start();
public:
    GameStart();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
    void playMusic();

};

