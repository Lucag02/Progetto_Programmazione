//
// Created by luca on 24/06/22.
//
#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H
#include <random>
#include "PlayableCharacter.h"


class Enemy: public GameCharacter {
private:
    const static float moveTime;
    static float timer;
    bool active;
    CharacterType type;
    sf::Vector2i direction;
    bool dead;
    bool aggro;
    float attackDistance;
    bool hasHit;
public:
    Enemy(ResourceManager &resources, float x, float y, int type);
    bool isAggroed() const;
    void update(const float &dt, PlayableCharacter &player);
    void render(sf::RenderTarget &target) override;
    float distanceToPlayer(sf::Vector2f playerPos);
    static void updateTimer(const float &dt);
    static bool canChangeDirection();
    static void resetTimer();
    void setDirection(const sf::Vector2i &dir);
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
