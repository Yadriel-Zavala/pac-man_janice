#include "RandomFruit.h"

RandomFruit::RandomFruit(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height) {
        
    vector<ofImage> sprites;
    ofImage orange;
    ofImage lime;
    ofImage apple;

    //get fruit images
    orange.cropFrom(spriteSheet,522,50,10,15);
    lime.cropFrom(spriteSheet,555,49,10,15);
    apple.cropFrom(spriteSheet,538,50,10,15);

    //push images to vector of fruit sprites
    sprites.push_back(orange);
    sprites.push_back(lime);
    sprites.push_back(apple);

    //choose random fruit sprite for fruit
    this->sprite = sprites[rand() % sprites.size()];
}