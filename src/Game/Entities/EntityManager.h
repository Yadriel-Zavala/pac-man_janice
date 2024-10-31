#pragma once

#include "BoundBlock.h"

class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> boundBlocks;
	std::vector<Entity*> ghosts;
	void tick();
	void render();
	void setKillable(bool);
	ofImage spritesheet;
	int ghostBackTimer = 30;
	int i;

private:
	bool killable = false;
	int killableCounter;
};