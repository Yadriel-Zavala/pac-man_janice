#include "UltimatePowerup.h"

UltimatePowerup::UltimatePowerup(Player* p) {
    this->p = p;
}

void UltimatePowerup::activate() {
    //TODO sorting of powerup list
    int n = p->powerupList.size();
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n - i; j++) {
            if (p->powerupList[j] > p->powerupList[j + 1]) {
                // swap arr[j+1] and arr[j]
                Powerup* pw = p->powerupList[j];
                p->powerupList[j] = p->powerupList[j + 1];
                p->powerupList[j + 1] = pw;
            }
        }
    }
}

string UltimatePowerup::toString() {
    return "Ultimate";
}