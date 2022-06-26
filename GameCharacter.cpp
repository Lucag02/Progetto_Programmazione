//
// Created by luca on 21/06/22.
//

#include "GameCharacter.h"
GameCharacter::GameCharacter(ResourceManager &resources, float x, float y, int HP, int m, float movespeed,
                             float manaregen) :
        hp(HP),mana(m),moveSpeed(movespeed),manaRegen(manaregen),resources(resources),prevPos(sf::Vector2f(x,y)){}

void GameCharacter::undoMove() {
    sprite.setPosition(prevPos);
}

Hitbox& GameCharacter::getHitbox() {
    return *hitbox;
}
