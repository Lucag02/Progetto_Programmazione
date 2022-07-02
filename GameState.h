//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMESTATE_H
#define PROGETTO_PROGRAMMAZIONE_GAMESTATE_H

#include <sstream>
#include "States.h"
#include "PlayableCharacter.h"
#include "ResourceManager.h"
#include "Map.h"
class GameState: public States {
private:
    class Bar{
    private:
        sf::Vector2f offset;
        sf::RectangleShape container;
        sf::RectangleShape bar;
        const static float barHeight;
    public:
        Bar(float x,float y,float size,sf::Color color);
        void update(const sf::View &currentView, float width);
        void render(sf::RenderTarget& target);
    };
    sf::View view;
    std::unique_ptr<PlayableCharacter> player;
    std::unique_ptr<Map> map;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<ResourceManager> charactersResources;
    ResourceManager mapResources;
    std::unique_ptr<Bar> health;
    std::unique_ptr<Bar> stamina;
    //TODO put the miniMap in a vertx array to improve performance
    std::vector<std::vector<sf::RectangleShape>> miniMap;
    bool paused;
    bool miniMapOpen;
    const static float keyTime;
    float keyTimer;
    void loadTextures();
    void createMiniMap();
    void updateMiniMap();
    void renderMiniMap(sf::RenderTarget& target);
#if DEBUG
    float dT;
#endif
public:
    GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow* w);
    void update(const float& dt) override;
    void render(sf::RenderTarget &target) override;
    ~GameState() override;
};



#endif //PROGETTO_PROGRAMMAZIONE_GAMESTATE_H
