//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#include "GameCharacter.h"

class PlayableCharacter: public GameCharacter{
public:
    explicit PlayableCharacter(ResourceManager &resources, int HP = 10, int m = 0, float x = 0, float y = 0,
                               float movespeed = 100, float manaregen = 2);
    sf::Vector2f getPosition();
    bool isAnimationLocked() const;
    void setAnimationLock(bool lock);
    bool isAnimationPlaying();
    void update(const float &dt) override;
    void render(sf::RenderTarget& target) override;
    void setPosition(float x, float y);
    ~PlayableCharacter() override;
private:
    bool animationLock;
    bool hardLock;
    std::string animation;
    std::string lockAnimation;
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
