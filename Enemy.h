//
// Created by luca on 24/06/22.
//
#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H
#include "GameCharacter.h"
enum class enemyType{SKELETON=0,SLIME=1};

class Enemy: public GameCharacter {
private:
    bool active;
    enemyType type;
public:
    Enemy(ResourceManager &resources, float x, float y, int type);
    void update(const float &dt) override;
    void render(sf::RenderTarget &target) override;
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
