#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "Cherry.h"
#include "Strawberry.h"
#include "RandomFruit.h"
#include "CherryPowerup.h"
#include "StrawberryPowerup.h"
#include "RandomPowerup.h"
#include "UltimateKey.h"
#include "UltimatePowerup.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;

    moving = MLEFT;
    
}
void Player::tick(){

    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        walkUp->tick();
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
    }

    if(invisCounter < 0){
        this->renderEntity = true;
        this->isKillable = true;
        this->unkillableTimer = 30*10;
    }

    if(score >= 1000 && !ultimateKeySpawned){
        spritesheet.load("images/Background.png");
        Entity* entity;
        
        do {
            entity = em->entities[rand()%em->entities.size()];
        } while(dynamic_cast<Dot*>(entity) == nullptr);
        UltimateKey* ultKey = new UltimateKey(entity->getPosX(), entity->getPosX(), 16, 16, spritesheet);
        em->entities.push_back(ultKey);
        ultimateKeySpawned = true;
        entity->remove = true;
    }

    if(unkillableTimer <= 0) {
        this->isKillable = true;
    } else {
        unkillableTimer--;
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());

    if(facing == UP)
        walkUp->getCurrentFrame().draw(x, y, width, height);
    else if(facing == DOWN)
        walkDown->getCurrentFrame().draw(x, y, width, height);
    else if(facing == LEFT)
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    else if(facing == RIGHT)
        walkRight->getCurrentFrame().draw(x, y, width, height);
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);

    string pws = "Powerups: ";
    for(Powerup* p: powerupList) {
        pws += p->toString();
        pws += ", ";
    } 
    pws.erase(pws.begin() + pws.length()-1);
    ofDrawBitmapString(pws, ofGetWidth()/2-200,  ofGetHeight()-50);
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
            // If Pacman already has 3 lives, pressing ’m’ will not give him another life
        case 'm':
        if (health < 3)
            health++;
            break;
            // Winstate
        case 'y':
            for (Entity *entity : em->entities){
                if (dynamic_cast<Dot *>(entity) || dynamic_cast<BigDot *>(entity)){
                    entity->remove = true;
                }
            }   
            break;
        case ' ':
            if(powerupList.size() > 0) {
                powerupList[0]->em = this->em;
                powerupList[0]->activate();
                powerupList.erase(powerupList.begin());
            }
            break;
        case 'p':
            score = 1000;
            break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
FACING Player::getFacing(){ return facing; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }
void Player::setPosX(int posX){ this->x = posX; }
void Player::setPosY(int posY){ this->y = posY; }

void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=20;
                em->setKillable(true);
                this->isKillable = false;
            }
            if(dynamic_cast<Cherry*>(entity)){
                powerupList.push_back(new CherryPowerup(this));
                entity->remove = true;
            }
            if(dynamic_cast<Strawberry*>(entity)){
                //strawberry collision
                powerupList.push_back(new StrawberryPowerup(this));
                entity->remove = true;
            }
            if(dynamic_cast<RandomFruit*>(entity)){
                //strawberry collision
                powerupList.push_back(new RandomPowerup(this));
                entity->remove = true;
            }
            if(dynamic_cast<UltimateKey*>(entity)) {
                UltimatePowerup* sorter = new UltimatePowerup(this);
                sorter->activate();
                entity->remove = true;
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()) {
                ghost->remove = true;
                ghost->hasBeenEaten = true;
            }
            else {
               if(this->isKillable && ghost->noCollision == false) die();
            }
        }
    }

    
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}

int Player::getDots(){

    int numdots;
    for (Entity *d : em->entities){
        if (dynamic_cast<Dot *>(d) || dynamic_cast<BigDot *>(d))
        {
            numdots++;
        }
    }
    return numdots;
}