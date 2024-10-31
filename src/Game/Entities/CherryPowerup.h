#pragma once
#include "Powerup.h"
#include "Player.h"

class CherryPowerup: public Powerup {
    public:
        void activate();
        CherryPowerup(Player* p);
        Player* p;
        string toString();
    
    private:
        int rank = 1;
};