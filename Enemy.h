//
// Created by luca on 24/06/22.
//
#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H
#include <random>
#include "PlayableCharacter.h"
enum class enemyType{SKELETON=0,SLIME=1};

class Enemy: public GameCharacter {
private:
    const static float moveTime;
    float timer;
    bool active;
    enemyType type;
    sf::Vector2i direction;
public:
    Enemy(ResourceManager &resources, float x, float y, int type);
    void update(const float &dt, PlayableCharacter &player);
    void render(sf::RenderTarget &target) override;
    float distanceToPlayer(sf::Vector2f playerPos);
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
