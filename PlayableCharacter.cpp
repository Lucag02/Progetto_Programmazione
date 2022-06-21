//
// Created by luca on 21/06/22.
//

#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(int HP, int m, float x, float y, float movespeed, float manaregen) : GameCharacter(
        HP, m, x, y, movespeed, manaregen) {}

void PlayableCharacter::update(const float &dt) {

}

void PlayableCharacter::render(sf::RenderTarget &target) {

}

PlayableCharacter::~PlayableCharacter() {

}
