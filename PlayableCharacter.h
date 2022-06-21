//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#include "GameCharacter.h"

class PlayableCharacter: public GameCharacter{
public:
    sf::Vector2f getPosition();
    explicit PlayableCharacter(const ResourceManager &resources, int HP = 10, int m = 0, float x = 0, float y = 0,
                               float movespeed = 1000, float manaregen = 2);
    void update(const float &dt) override;
    void render(sf::RenderTarget& target) override;
    ~PlayableCharacter() override;
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
