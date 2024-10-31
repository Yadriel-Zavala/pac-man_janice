#include "Cherry.h"

Cherry::Cherry(int x, int y,int width ,int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,490,48,13,15);
}