#include "CherryPowerup.h"
#include "Entity.h"


CherryPowerup::CherryPowerup(Player* p) {
    this->p = p;
}

void CherryPowerup::activate() {
    Entity* toTeleport = em->entities[ofRandom(em->entities.size())];
    p->setPosX(toTeleport->getPosX());
    p->setPosY(toTeleport->getPosY());
}

string CherryPowerup::toString() {
    return "Cherry";
}