//
// Created by luca on 21/06/22.
//

#include "GameCharacter.h"
GameCharacter::GameCharacter(ResourceManager &resources, int HP, int m, float x, float y, float movespeed,
                             float manaregen) :
        hp(HP),mana(m),moveSpeed(movespeed),manaRegen(manaregen),resources(resources){}
