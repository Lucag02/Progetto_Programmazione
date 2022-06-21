//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class GameCharacter {
protected:
    sf::Sprite* sprite;
    float moveSpeed;
    int hp;
    int mana;
    float manaRegen;
public:
    explicit GameCharacter(int HP=10,int m=0,float x=0, float y=0,float movespeed=100,float manaregen=2);
    virtual void update(const float& dt)=0;
    virtual void render(sf::RenderTarget &target)=0;
    virtual ~GameCharacter()=default;
};



#endif //PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
