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
#include "Item.h"
#include "Button.h"
class GameState: public States {
private:
    class Inventory{
    private:
        int size;
        sf::RectangleShape background;
        std::vector<sf::RectangleShape> containers;
        std::list<std::unique_ptr<Item>> items;
    public:
        Inventory();
        void updatePosition(sf::Vector2f viewPos);
        void update(PlayableCharacter &player, sf::Vector2f mousePos,
                    std::list<std::unique_ptr<Item>> &groundItems);
        void render(sf::RenderTarget& target);
        std::list<std::unique_ptr<Item>>& getItems();
    };
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
    Inventory inventory;
    sf::RectangleShape background;
    sf::View view;
    std::unique_ptr<PlayableCharacter> player;
    std::unique_ptr<Map> map;
    std::list<std::unique_ptr<Enemy>> enemies;
    std::vector<ResourceManager> charactersResources;
    std::vector<ResourceManager> abilityResources;
    std::unique_ptr<Button> mainMenuBTN;
    sf::Texture tileMap;
    std::unique_ptr<Bar> health;
    std::unique_ptr<Bar> stamina;
    std::unique_ptr<Bar> mana;
    sf::VertexArray miniMap;
    std::list<std::unique_ptr<Item>> groundItems;
    sf::Font font;
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
    GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w, CharacterType playerType=KNIGHT);
    void update(const float& dt) override;
    void render(sf::RenderTarget &target) override;
    ~GameState() override;
};



#endif //PROGETTO_PROGRAMMAZIONE_GAMESTATE_H
