//
// Created by luca on 21/06/22.
//

#include "GameState.h"

GameState::GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) :view(w->getView()) {
    window=w;
    this->states=states;
    for (int i=KNIGHT;i<=SKELETON;i++)
        charactersResources.emplace_back();
    loadTextures();
    player=std::make_unique<PlayableCharacter>(charactersResources[KNIGHT]);
    map=std::make_unique<Map>(mapResources.getTexture("TILES"),charactersResources,*player,enemies);
    health=std::make_unique<Bar>(5,5,player->getHealth(),sf::Color::Red);
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
    map->update(dt);
    view.setCenter(player->getPosition());
    window->setView(view);
    health->update(view, player->getHealth());
}

void GameState::render(sf::RenderTarget &target) {
    map->render(target);
    for(auto& enemy: enemies)
        enemy->render(target);
    player->render(target);
    health->render(target);
    updateMousePos();
#if DEBUG
    sf::Text mousePosText;
    sf::Font font;
    font.loadFromFile("../Config/ComicSans.ttf");
    sf::Text dt;
    dt.setFont(font);
    dt.setCharacterSize(15);
    dt.setPosition(mousePos.x+10,mousePos.y-5);
    dt.setString(std::to_string(1/dT));
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
    charactersResources[KNIGHT].addTexture("KNIGHT","../Resources/Knight.png");
    charactersResources[SKELETON].addTexture("SKELETON","../Resources/Skeleton.png");
    charactersResources[SLIME].addTexture("SLIME","../Resources/Slime.png");
    charactersResources[KNIGHT].addAnimation(AnimationName::ATTACK, 50, 37, 0, 4, 9, 4, 90);
    charactersResources[KNIGHT].addAnimation(AnimationName::IDLE, 50, 37, 0, 0, 3, 0, 100);
    charactersResources[KNIGHT].addAnimation(AnimationName::MOVE, 50, 37, 0, 1, 5, 1, 100);
    charactersResources[KNIGHT].addAnimation(AnimationName::DEATH, 50, 37, 0, 9, 4, 9, 100, false);
    charactersResources[KNIGHT].addAnimation(AnimationName::ROLL, 50, 37, 0, 8, 4, 8, 100);
    charactersResources[SKELETON].addAnimation(AnimationName::MOVE, 50, 48, 0, 2, 5, 2, 150);
    charactersResources[SKELETON].addAnimation(AnimationName::ATTACK, 50, 48, 0, 1, 5, 1, 200);
    charactersResources[SKELETON].addAnimation(AnimationName::DEATH, 50, 48, 0, 3, 5, 3, 150, false);
    charactersResources[SLIME].addAnimation(AnimationName::MOVE, 32, 25, 0, 4, 3, 4, 150);
    charactersResources[SLIME].addAnimation(AnimationName::ATTACK, 32, 25, 0, 0, 4, 0, 200);
    charactersResources[SLIME].addAnimation(AnimationName::DEATH, 32, 25, 0, 1, 3, 1, 150, false);
}
GameState::~GameState() {}

const float GameState::Bar::barHeight=10;
GameState::Bar::Bar(float x, float y, float size, sf::Color color):offset(sf::Vector2f(x,y)) {
    container.setPosition(x,y);
    container.setSize(sf::Vector2f(size,barHeight));
    container.setFillColor(sf::Color::Transparent);
    container.setOutlineThickness(2);
    container.setOutlineColor(color);
    bar.setPosition(x,y);
    bar.setSize(sf::Vector2f(size,barHeight));
    bar.setFillColor(color);
    bar.setOutlineThickness(0);
    bar.setOutlineColor(sf::Color::Transparent);
}

void GameState::Bar::update(const sf::View &currentView, float width) {
    sf::Vector2f viewSize=sf::Vector2f (currentView.getSize().x/2,currentView.getSize().y/2);
    container.setPosition(currentView.getCenter()-viewSize+offset);
    bar.setPosition(currentView.getCenter()-viewSize+offset);
    if(width>0)
        bar.setSize(sf::Vector2f(width,barHeight));
    else
        bar.setSize(sf::Vector2f(0,barHeight));
}

void GameState::Bar::render(sf::RenderTarget &target) {
    target.draw(container);
    target.draw(bar);
}