//
// Created by luca on 24/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H
#include "GameCharacter.h"

class Enemy:public GameCharacter {
private:
    bool active;
public:
    Enemy()=default;
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
