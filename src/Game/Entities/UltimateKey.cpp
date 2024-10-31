#include "UltimateKey.h"

UltimateKey::UltimateKey(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 600, 50, 16, 16);
}