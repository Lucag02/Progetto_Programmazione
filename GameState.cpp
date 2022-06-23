//
// Created by luca on 21/06/22.
//

#include "GameState.h"

GameState::GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) :view(w->getView()) {
    window=w;
    this->states=states;
    loadTextures();
    player=std::make_unique<PlayableCharacter>(playerResources);
}

void GameState::update(const float &dt) {
    player->update(dt);
    if(player->isAnimationLocked()&&!player->isAnimationPlaying())
        player->setAnimationLock(false);
    view.setCenter(player->getPosition());
    window->setView(view);

}

void GameState::render(sf::RenderTarget &target) {
    player->render(target);
}

void GameState::loadTextures() {
    std::string filepath;
    std::string name;
    filepath="../Resources/_Idle.png";
    name="IDLE_ANIMATION";
    playerResources.addTexture(name, filepath);
    playerResources.addAnimation(name, 120, 80, 0, 0, 9, 0, 100);
    name="ATTACK_ANIMATION";
    filepath="../Resources/_Attack.png";
    playerResources.addTexture(name, filepath);
    playerResources.addAnimation(name, 120, 80, 0, 0, 3, 0, 100);
    name="RUN_ANIMATION";
    filepath="../Resources/_Run.png";
    playerResources.addTexture(name, filepath);
    playerResources.addAnimation(name, 120, 80, 0, 0, 9, 0, 100);
    name="DEATH_ANIMATION";
    filepath="../Resources/_Death.png";
    playerResources.addTexture(name, filepath);
    playerResources.addAnimation(name, 120, 80, 0, 0, 9, 0, 100);
    name="ROLL_ANIMATION";
    filepath="../Resources/_Roll.png";
    playerResources.addTexture(name, filepath);
    playerResources.addAnimation(name, 120, 80, 0, 0, 11, 0, 50);
}
GameState::~GameState() {

}
