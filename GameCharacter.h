//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class GameCharacter {
protected:
    sf::Sprite sprite;
    float moveSpeed;
    int hp;
    int mana;
    float manaRegen;
    ResourceManager& resources;
public:
    explicit GameCharacter( ResourceManager &resources, int HP, int m, float x, float y, float movespeed,
                           float manaregen);
    virtual void update(const float& dt)=0;
    virtual void render(sf::RenderTarget &target)=0;
    virtual ~GameCharacter()=default;
};



#endif //PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
