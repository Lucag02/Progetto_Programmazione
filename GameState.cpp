//
// Created by luca on 21/06/22.
//

#include "GameState.h"

GameState::GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) :view(w->getView()) {
    window=w;
    this->states=states;
    loadTextures();
    player=std::make_unique<PlayableCharacter>(playerResources);
    map=std::make_unique<Map>(mapResources.getTexture("TILES"),*player);
}

void GameState::update(const float &dt) {
    player->update(dt);
    if(player->isAnimationLocked()&&!player->isAnimationPlaying())
        player->setAnimationLock(false);

}

void GameState::render(sf::RenderTarget &target) {
    map->render(target);
    view.setCenter(player->getPosition());
    window->setView(view);
    player->render(target);
}

void GameState::loadTextures() {
    mapResources.addTexture("TILES","../Resources/DungeonCrawl_ProjectUtumnoTileset.png");
    playerResources.addTexture("IDLE_ANIMATION", "../Resources/_Idle.png");
    playerResources.addAnimation("IDLE_ANIMATION", 120, 80, 0, 0, 9, 0, 100);
    playerResources.addTexture("ATTACK_ANIMATION", "../Resources/_Attack.png");
    playerResources.addAnimation("ATTACK_ANIMATION", 120, 80, 0, 0, 3, 0, 100);
    playerResources.addTexture("RUN_ANIMATION", "../Resources/_Run.png");
    playerResources.addAnimation("RUN_ANIMATION", 120, 80, 0, 0, 9, 0, 100);
    playerResources.addTexture("DEATH_ANIMATION", "../Resources/_Death.png");
    playerResources.addAnimation("DEATH_ANIMATION", 120, 80, 0, 0, 9, 0, 100);
    playerResources.addTexture("ROLL_ANIMATION", "../Resources/_Roll.png");
    playerResources.addAnimation("ROLL_ANIMATION", 120, 80, 0, 0, 11, 0, 50);
}
GameState::~GameState() {

}
