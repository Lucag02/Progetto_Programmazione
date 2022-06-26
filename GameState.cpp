//
// Created by luca on 21/06/22.
//

#include "GameState.h"

GameState::GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) :view(w->getView()) {
    window=w;
    this->states=states;
    loadTextures();
    player=std::make_unique<PlayableCharacter>(playerResources);
    map=std::make_unique<Map>(mapResources.getTexture("TILES"),enemyResources,*player,enemies);
}

void GameState::update(const float &dt) {
#if DEBUG
    dT=dt;
#endif
    player->update(dt);
    if(player->isAnimationLocked()&&!player->isAnimationPlaying())
        player->setAnimationLock(false);
    for(auto& enemy:enemies)
        enemy->update(dt);
    map->update();
}

void GameState::render(sf::RenderTarget &target) {
    map->render(target);
    //FIXME fix camera going out of bounds
    view.setCenter(player->getPosition());
    window->setView(view);
    for(auto& enemy: enemies)
        enemy->render(target);
    player->render(target);
    updateMousePos();
#if DEBUG
    sf::Text mousePosText;
    sf::Font font;
    font.loadFromFile("../Config/ComicSans.ttf");
    sf::Text dt;
    dt.setFont(font);
    dt.setCharacterSize(15);
    dt.setPosition(mousePos.x,mousePos.y-5);
    dt.setString(std::to_string(dT));
    mousePosText.setFont(font);
    mousePosText.setCharacterSize(15);
    mousePosText.setPosition(mousePos.x,mousePos.y-25);
    std::stringstream ss;
    ss<<mousePos.x<<"  "<<mousePos.y;
    mousePosText.setString(ss.str());
    window->draw(dt);
    window->draw(mousePosText);
#endif
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
    enemyResources.addTexture("SKELETON_MOVE","../Resources/Skeleton_Walk.png");
    enemyResources.addAnimation("SKELETON_MOVE",50, 48, 0, 0, 5, 0, 150);
    enemyResources.addTexture("SLIME_MOVE","../Resources/Slime_Walk.png");
    enemyResources.addAnimation("SLIME_MOVE",32, 25, 0, 0, 3, 0, 150);
}
GameState::~GameState() {

}
