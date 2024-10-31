#include "PauseState.h"

PauseState::PauseState(){
    music.stop();
    resumeButton = new Button(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 64, 50, "RESUME");
    quitButton = new Button(ofGetWindowWidth()/2, ofGetWindowHeight()/2 + 60, 64, 50, "QUIT");
}
void PauseState::tick(){
    resumeButton->tick();
    quitButton->tick();
    if(resumeButton->wasPressed()){      
        setNextState("Game");
        setFinished(true);
    }
    if(quitButton->wasPressed()){
        setNextState("over");
        setFinished(true);
    }
}
void PauseState::render(){
    ofDrawBitmapString("PAUSED", ofGetWidth()/2 - 10, ofGetHeight()/2-300, 50);
    ofDrawBitmapString("SCORE: " + to_string(score), ofGetWidth()/2 + 250, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	resumeButton->render();
    quitButton->render();
}
void PauseState::keyPressed(int key){
    
}
void PauseState::reset(){
    setFinished(false);
    setNextState("");
    resumeButton->reset();
    quitButton->reset();
}
void PauseState::mousePressed(int x, int y, int button){
    resumeButton->mousePressed(x,y);
    quitButton->mousePressed(x,y);
}
PauseState::~PauseState(){
    delete resumeButton;
    delete quitButton;
}

void PauseState::setScore(int sc){
    score = sc;
}