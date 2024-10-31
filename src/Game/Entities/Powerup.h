#pragma once
#include "Entity.h"
#include "EntityManager.h"

// Abstract Powerup class

class Powerup {
    public:
        int rank;
        EntityManager* em;
        Entity* p = 0;
        virtual void activate() = 0; // pure virtual function
        virtual string toString() = 0;
};
/*
class Powerup_debug : public Powerup // the abstract class is inherited
{
    char Pacman; // Declared variables
    char const sprite sf;
    int Powerup;    // Defining the debug Powerup

    public: powerup_debug(sf == ' ')
        int activate()
    {
        sf++;
        cout << " the Pacman ran faster and ate all ghosts";
        return Pacman;
    }
};
*/

// The player selection depending on
//  which one he wants to play as
// Addresses for different subclasses
// Have been passed through a pointer
/*
int main()
{
    Powerup *p;
    Debug d;
    p = &d;
    D->activate();
    Cherry ch;
    p = &ch;
    ch->activate();
    Strawberry St;
    p = &st;
    st->activate();
    Random r;
    p = &r;
    r->activate();
    chooseplayerstate cps;
    p = &cps;
    cps->activate();
    return 0;
}
*/