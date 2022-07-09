//
// Created by luca on 21/06/22.
//

#include "GameState.h"
const float GameState::keyTime=300;
GameState::GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w, CharacterType playerType)
        : view(w->getView()), keyTimer(0),
          paused(false), miniMapOpen(false), miniMap(sf::VertexArray(sf::Quads)){
    window=w;
    this->states=states;
    for (int i=KNIGHT;i<=SKELETON;i++)
        charactersResources.emplace_back();
    for(int i=THUNDER;i<=THUNDER_STORM;i++)
        abilityResources.emplace_back();
    loadTextures();
    player=std::make_unique<PlayableCharacter>(charactersResources[playerType],abilityResources,playerType);
    map=std::make_unique<Map>(tileMap,charactersResources,*player,enemies);
    health=std::make_unique<Bar>(5,5,player->getHealth(),sf::Color::Red);
    stamina=std::make_unique<Bar>(5,20,player->getStamina(),sf::Color::Green);
    createMiniMap();
    background.setSize(view.getSize());
    background.setFillColor(sf::Color(0,0,0,100));
    mainMenuBTN=std::make_unique<Button>(325.f,450.f,150.f,50.f,"Main Menu",font);

}

void GameState::update(const float &dt) {
#if DEBUG
    dT=dt;
#endif
    updateMousePos();
    keyTimer+=dt*1000;
    if(keyTimer>keyTime) {
        sf::Vector2f viewPos=sf::Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
        background.setPosition(viewPos);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            inventory.updatePosition(viewPos);
            mainMenuBTN->setPosition(sf::Vector2f(viewPos.x+10,viewPos.y+390));
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
        player->update(dt, mousePos);
        if (player->isAnimationLocked() && !player->isAnimationPlaying())
            player->setAnimationLock(false);
        auto enemy=enemies.begin();
        while(enemy!=enemies.end()) {
            (*enemy)->update(dt, *player);
            auto nextEnemy=++enemy;
            enemy--;
            if((*enemy)->isDead()&&!(*enemy)->isDying()){
                if(rand()%5==1)
                    groundItems.emplace_back(std::make_unique<Item>(tileMap,font,(*enemy)->getPosition().x,(*enemy)->getPosition().y,rand()%Item::numItems));
                enemies.erase(enemy);
            }
            enemy=nextEnemy;
        }
        auto item=groundItems.begin();
        while(item!=groundItems.end()){
            auto nextItem=++item;
            (*(--item))->update(*player, mousePos, groundItems, inventory.getItems());
            item=nextItem;;
        }
        map->update(dt);
        view.setCenter(player->getPosition());
        window->setView(view);
        health->update(view, player->getHealth());
        stamina->update(view, player->getStamina());
    }
    else {
        if(!miniMapOpen) {
            mainMenuBTN->update(mousePos);
            inventory.update(*player, mousePos, groundItems);
            health->update(view, player->getHealth());
            if(mainMenuBTN->isPressed()) {
                auto tmp=std::move(states->top());
                states->pop();
                states->pop();
            }
        }
    }
}

void GameState::render(sf::RenderTarget &target) {
    map->render(target);
    for(auto& item:groundItems)
        item->render(target);
    for(auto& enemy: enemies) {
        enemy->render(target);
    }
    player->render(target);
    health->render(target);
    stamina->render(target);
    if(paused) {
        target.draw(background);
        if(miniMapOpen)
            renderMiniMap(target);
        else {
            inventory.render(target);
            mainMenuBTN->render(target);
        }
    }

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
    font.loadFromFile("../Config/ComicSans.ttf");
    tileMap.loadFromFile("../Resources/DungeonCrawl_ProjectUtumnoTileset.png");
    charactersResources[KNIGHT].addTexture("KNIGHT","../Resources/Knight.png");
    charactersResources[MAGE].addTexture("MAGE","../Resources/Battle_mage.png");
    charactersResources[SKELETON].addTexture("SKELETON","../Resources/Skeleton.png");
    charactersResources[SLIME].addTexture("SLIME","../Resources/Slime.png");
    abilityResources[THUNDER].addTexture("PROJECTILE","../Resources/Thunder.png");
    abilityResources[THUNDER_STORM].addTexture("PROJECTILE","../Resources/Thunder_2.png");
    charactersResources[KNIGHT].addAnimation(AnimationName::ATTACK, 50, 37, 0, 4, 9, 4, 90);
    charactersResources[KNIGHT].addAnimation(AnimationName::IDLE, 50, 37, 0, 0, 3, 0, 100);
    charactersResources[KNIGHT].addAnimation(AnimationName::MOVE, 50, 37, 0, 1, 5, 1, 100);
    charactersResources[KNIGHT].addAnimation(AnimationName::DEATH, 50, 37, 0, 9, 4, 9, 100, false);
    charactersResources[KNIGHT].addAnimation(AnimationName::ROLL, 50, 37, 0, 8, 4, 8, 100);
    charactersResources[KNIGHT].addAnimation(AnimationName::ABILITY, 50, 37, 0, 3, 8, 3, 100);
    charactersResources[MAGE].addAnimation(AnimationName::ATTACK, 56, 48, 0, 1, 7, 1, 90);
    charactersResources[MAGE].addAnimation(AnimationName::IDLE, 56, 48, 0, 4, 7, 4, 100);
    charactersResources[MAGE].addAnimation(AnimationName::MOVE, 56, 48, 0, 5, 9, 5, 100);
    charactersResources[MAGE].addAnimation(AnimationName::DEATH, 56, 48, 0, 3, 11, 3, 100, false);
    charactersResources[MAGE].addAnimation(AnimationName::ROLL, 56, 48, 0, 2, 6, 2, 100);
    charactersResources[MAGE].addAnimation(AnimationName::ABILITY, 56, 48, 0, 0, 9, 0, 100);
    charactersResources[SKELETON].addAnimation(AnimationName::MOVE, 50, 48, 0, 2, 5, 2, 150);
    charactersResources[SKELETON].addAnimation(AnimationName::ATTACK, 53, 48, 0, 1, 5, 1, 200);
    charactersResources[SKELETON].addAnimation(AnimationName::DEATH, 50, 48, 0, 0, 5, 0, 150, false);
    charactersResources[SLIME].addAnimation(AnimationName::MOVE, 32, 25, 0, 4, 3, 4, 150);
    charactersResources[SLIME].addAnimation(AnimationName::ATTACK, 32, 25, 0, 0, 4, 0, 200);
    charactersResources[SLIME].addAnimation(AnimationName::DEATH, 32, 25, 0, 1, 3, 1, 150, false);
    abilityResources[THUNDER].addAnimation(AnimationName::MOVE,32,32,0,0,4,0,100);
    abilityResources[THUNDER].addAnimation(AnimationName::EXPLOSION,32,32,0,1,5,1,100,false);
    abilityResources[THUNDER_STORM].addAnimation(AnimationName::MOVE,48,48,0,0,15,0,100);
    abilityResources[THUNDER_STORM].addAnimation(AnimationName::EXPLOSION,32,48,0,1,5,1,100, false);
}
void GameState::createMiniMap() {
    const std::vector<std::vector<Map::Tile>>& mapLayout=map->getMap();
    sf::Vector2i size=map->getMapSize();
    miniMap.resize(size.x*size.y*4);
    for(int i=size.x-1;i>=0;i--) {
        for (int j = size.y-1; j >=0; j--) {
            sf::Vertex* quad=&miniMap[(i*size.y+j)*4];
            switch(mapLayout[i][j].type) {
                case Map::TileType::TERRAIN:
                    quad[0].color=sf::Color(140,107,83);
                    quad[1].color=sf::Color(140,107,83);
                    quad[2].color=sf::Color(140,107,83);
                    quad[3].color=sf::Color(140,107,83);
                    break;
                case Map::TileType::GRASS:
                    quad[0].color=sf::Color(0,100,0);
                    quad[1].color=sf::Color(0,100,0);
                    quad[2].color=sf::Color(0,100,0);
                    quad[3].color=sf::Color(0,100,0);
                    break;
                case Map::TileType::WALL:
                    quad[0].color=sf::Color(170,170,10);
                    quad[1].color=sf::Color(170,170,10);
                    quad[2].color=sf::Color(170,170,10);
                    quad[3].color=sf::Color(170,170,10);
                    break;
                case Map::TileType::VOID:
                    quad[0].color=sf::Color::Black;
                    quad[1].color=sf::Color::Black;
                    quad[2].color=sf::Color::Black;
                    quad[3].color=sf::Color::Black;
                    break;
            }
        }
    }
}

void GameState::updateMiniMap() {
    sf::Vector2i size=map->getMapSize();
    sf::Vector2f topLeft(view.getCenter().x-size.x/2,view.getCenter().y-size.y/2);
    for(int i=0;i<size.x;i++)
        for(int j=0;j<size.y;j++) {
            sf::Vertex* quad=&miniMap[(j+i*size.y)*4];
            quad[0].position = (sf::Vector2f(topLeft.x + i, topLeft.y + j));
            quad[1].position = (sf::Vector2f(topLeft.x + i+1, topLeft.y + j));
            quad[2].position = (sf::Vector2f(topLeft.x + i+1, topLeft.y + j+1));
            quad[3].position = (sf::Vector2f(topLeft.x + i, topLeft.y + j+1));
        }
}

void GameState::renderMiniMap(sf::RenderTarget &target) {
    target.draw(miniMap);
    sf::Vector2i size=map->getMapSize();
    sf::RectangleShape playerMarker;
    playerMarker.setSize(sf::Vector2f(5,5));
    playerMarker.setFillColor(sf::Color::Red);
    playerMarker.setPosition(view.getCenter().x-size.x/2+player->getPosition().x/map->getTileWidth(),
                             view.getCenter().y-size.y/2+player->getPosition().y/map->getTileHeight());
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

GameState::Inventory::Inventory():size(32) {
    background.setSize(sf::Vector2f(600,320));
    background.setFillColor(sf::Color(0,0,0,100));
    for(int i=0;i<size;i++)
        containers.emplace_back();
    for(auto& i:containers) {
        i.setFillColor(sf::Color(224,224,224,100));
        i.setSize(sf::Vector2f(64,64));
    }
}

void GameState::Inventory::updatePosition(sf::Vector2f viewPos) {
    background.setPosition(viewPos.x+100,viewPos.y+55);
    int sizeX=background.getSize().x/containers[0].getSize().x-1;
    int sizeY=background.getSize().y/containers[0].getSize().y-1;
    for(int i=0;i<sizeX;i++)
        for(int j=0;j<sizeY;j++)
            containers[i*sizeY+j].setPosition(viewPos.x+110+i*74,viewPos.y+65+j*74);
    int i=0;
    for(auto& item:items) {
        item->setPosition(containers[i++].getPosition());
    }
}

void GameState::Inventory::render(sf::RenderTarget &target) {
    target.draw(background);
    for(const auto& container:containers)
        target.draw(container);
    for(auto& item:items)
        item->render(target);
}

std::list<std::unique_ptr<Item>> &GameState::Inventory::getItems() {
    return items;
}

void GameState::Inventory::update(PlayableCharacter &_player, sf::Vector2f mousePos,
                                  std::list<std::unique_ptr<Item>> &ground_items) {
    auto item=items.begin();
    while(item!=items.end()){
        auto nextItem=++item;
        (*(--item))->update(_player, mousePos, ground_items, items);
        item=nextItem;;
    }
}
