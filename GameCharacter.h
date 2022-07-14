//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
#include <list>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Hitbox.h"
#include "Projectile.h"
#define DEBUG 0
enum CharacterType: int {KNIGHT=0,MAGE=1,SLIME=2,SKELETON=3};
class GameCharacter {
protected:
    std::unique_ptr<Hitbox> hitbox;
    sf::Sprite sprite;
    float moveSpeed;
    int hp;
    float mana;
    float manaRegen;
    ResourceManager resources;
    sf::Vector2f prevPos;
    std::unique_ptr<Hitbox> damageHitbox;
    bool damageActive;
    sf::Vector2f scaleFactor;
    AnimationName animation;
public:
    explicit GameCharacter(ResourceManager &resources, float x = 0, float y = 0, int HP = 10, int m = 0,float movespeed = 100,
                           float manaregen = 2);
    Hitbox & getHitbox();
    void undoMove();
    virtual void render(sf::RenderTarget &target)=0;
    virtual ~GameCharacter()=default;
};



#endif //PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
