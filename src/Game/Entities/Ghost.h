#pragma once

#include "EntityManager.h"
#include "Animation.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        void render();
        bool getKillable();
        void setKillable(bool);
        void backtrack();
        vector<int> previousCoordsX;
        vector<int> previousCoordsY;
        bool hasBeenEaten = false;
        ofImage spritesheet;
        int i, j;
        string color;
        bool noCollision = false;
        bool killable;
    private:
        bool previousCoordsSet = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=2;
        EntityManager* em;
        Animation* killableAnim;
        ofImage oldSprite;
        

        

};