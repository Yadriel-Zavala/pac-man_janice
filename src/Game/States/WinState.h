#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h"
#include "MapBuilder.h"

class WinState : public State{

private:
    ofImage img1;
    Button *startButton;
    Animation* anim;
    int score = 0;
    ofImage mapImage;
    Map* map;
    int finalScore = 0;

public:
    WinState();
    ~WinState();
    void tick();
    void render();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void reset();
    int getFinalScore();
    void setScore(int);
};