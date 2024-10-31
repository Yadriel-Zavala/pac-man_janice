#include "GameState.h"
#include "Entity.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map3.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
	if(map->getPlayer()->getHealth() == 0){
        setFinished(true);
        setNextState("over");
        map->getPlayer()->setHealth(3);
        finalScore = map->getPlayer()->getScore();
        map->getPlayer()->setScore(0);
        GameState(); {
        music.load("music/pacman_chomp.wav");
        mapImage.load("images/map3.png");
        map = MapBuilder().createMap(mapImage);
        }

	}
	if(map->getPlayer()->getDots() == 0){
        setFinished(true);
        setNextState("Win");
        mapImage.load("images/map3.png");
        map = MapBuilder().createMap(mapImage);
    }		
	}

void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
	if(key == 'p'){
		setFinished(true);
		setNextState("Pause");
	}
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}

int GameState::getFinalScore(){
	return finalScore;
}

GameState::~GameState(){
	delete map;
}