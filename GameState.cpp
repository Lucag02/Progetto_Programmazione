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
        enemy->update(dt, *player);
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
    playerResources.addTexture("PLAYER","../Resources/Player.png");
    enemyResources.addTexture("SKELETON","../Resources/Skeleton.png");
    enemyResources.addTexture("SLIME","../Resources/Slime.png");
    playerResources.addAnimation("ATTACK_ANIMATION", "PLAYER", 120, 80, 0, 0, 3, 0, 100);
    playerResources.addAnimation("IDLE_ANIMATION", "PLAYER", 120, 80, 0, 1, 9, 1, 100);
    playerResources.addAnimation("RUN_ANIMATION", "PLAYER", 120, 80, 0, 3, 9, 3, 100);
    playerResources.addAnimation("DEATH_ANIMATION", "PLAYER", 120, 80, 4, 0, 13, 0, 100);
    playerResources.addAnimation("ROLL_ANIMATION", "PLAYER", 120, 80, 0, 2, 11, 2, 50);
    enemyResources.addAnimation("SKELETON_MOVE", "SKELETON", 50, 48, 0, 1, 5, 1, 150);
    enemyResources.addAnimation("SKELETON_DEATH","SKELETON", 50, 48, 0, 2, 5, 2, 150);
    enemyResources.addAnimation("SLIME_MOVE", "SLIME", 32, 25, 4, 0, 7, 0, 150);
    enemyResources.addAnimation("SLIME_DEATH", "SLIME", 32, 25, 1, 2, 4, 2, 150);
}
GameState::~GameState() {

}
