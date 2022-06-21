//
// Created by luca on 21/06/22.
//

#include "GameState.h"

GameState::GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) {
    window=w;
    this->states=states;
    player=PlayableCharacter();

}

void GameState::update(const float &dt) {

}

void GameState::render(sf::RenderTarget &target) {

}

GameState::~GameState() {

}
