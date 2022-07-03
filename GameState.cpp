//
// Created by luca on 21/06/22.
//

#include "GameState.h"
const float GameState::keyTime=300;
GameState::GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) :view(w->getView()),keyTimer(0),
        paused(false),miniMapOpen(false){
    window=w;
    this->states=states;
    for (int i=KNIGHT;i<=SKELETON;i++)
        charactersResources.emplace_back();
    loadTextures();
    player=std::make_unique<PlayableCharacter>(charactersResources[KNIGHT]);
    map=std::make_unique<Map>(mapResources.getTexture("TILES"),charactersResources,*player,enemies);
    health=std::make_unique<Bar>(5,5,player->getHealth(),sf::Color::Red);
    stamina=std::make_unique<Bar>(5,20,player->getStamina(),sf::Color::Green);
    createMiniMap();
}

void GameState::update(const float &dt) {
#if DEBUG
    dT=dt;
#endif
    keyTimer+=dt*1000;
    if(keyTimer>keyTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            keyTimer=0;
            paused = !paused;
            if(miniMapOpen)
                miniMapOpen=false;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            miniMapOpen = true;
            updateMiniMap();
            if(!paused)
                paused=true;
        }
    }
    if(!paused) {
        player->update(dt);
        if (player->isAnimationLocked() && !player->isAnimationPlaying())
            player->setAnimationLock(false);
        for (auto &enemy: enemies)
            enemy->update(dt, *player);
        map->update(dt);
        view.setCenter(player->getPosition());
        window->setView(view);
        health->update(view, player->getHealth());
        stamina->update(view, player->getStamina());
    }
}

void GameState::render(sf::RenderTarget &target) {
    map->render(target);
    for(auto& enemy: enemies)
        enemy->render(target);
    player->render(target);
    health->render(target);
    stamina->render(target);
    if(paused) {
        sf::RectangleShape background;
        background.setSize(view.getSize());
        background.setFillColor(sf::Color(0,0,0,100));
        background.setPosition(view.getCenter().x-view.getSize().x/2,view.getCenter().y-view.getSize().y/2);
        target.draw(background);
        if(miniMapOpen)
            renderMiniMap(target);
    }
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
void GameState::createMiniMap() {
    const std::vector<std::vector<Map::Tile>>& mapLayout=map->getMap();
    sf::Vector2i size=map->getMapSize();
    miniMap.resize(size.x);
    for(int i=size.x-1;i>=0;i--) {
        miniMap[i].resize(size.y);
        for (int j = size.y-1; j >=0; j--) {
            miniMap[i][j].setSize(sf::Vector2f(1, 1));
            switch(mapLayout[i][j].type) {
                case Map::TileType::TERRAIN:
                    miniMap[i][j].setFillColor(sf::Color(140,107,83));
                    break;
                case Map::TileType::GRASS:
                    miniMap[i][j].setFillColor(sf::Color(0,102,0));
                    break;
                case Map::TileType::WALL:
                    miniMap[i][j].setFillColor(sf::Color(170,170,10));
                    break;
                case Map::TileType::VOID:
                    miniMap[i][j].setFillColor(sf::Color::Black);
                    break;
            }
        }
    }
}

void GameState::updateMiniMap() {
    int sizeX=miniMap.size();
    int sizeY=miniMap[0].size();
    sf::Vector2f topLeft(view.getCenter().x-sizeX/2,view.getCenter().y-sizeY/2);
    for(int i=0;i<sizeX;i++)
        for(int j=0;j<sizeY;j++)
            miniMap[i][j].setPosition(topLeft.x+i,topLeft.y+j);
}

void GameState::renderMiniMap(sf::RenderTarget &target) {
    int sizeX=miniMap.size();
    int sizeY=miniMap[0].size();
    for(int i=0;i<sizeX;i++)
        for(int j=0;j<sizeY;j++) {
            target.draw(miniMap[i][j]);
        }
    sf::RectangleShape playerMarker;
    playerMarker.setSize(sf::Vector2f(5,5));
    playerMarker.setFillColor(sf::Color::Red);
    playerMarker.setPosition(view.getCenter().x-sizeX/2+player->getPosition().x/map->getTileWidth(),
                             view.getCenter().y-sizeY/2+player->getPosition().y/map->getTileHeight());
    target.draw(playerMarker);
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