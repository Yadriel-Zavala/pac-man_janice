#pragma once
#include "Powerup.h"
#include "Player.h"

class RandomPowerup : public Powerup {
    public:
        RandomPowerup(Player* p);
        void activate();
        Player* p;
        string toString();
        int compareTo(Powerup* p2) {
            return this->rank - p2->rank;
        }

    private:
        int rank = 3;
        
};