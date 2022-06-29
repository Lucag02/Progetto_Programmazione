//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#include "GameCharacter.h"
#include "Hitbox.h"
#define DEBUG 0
class PlayableCharacter: public GameCharacter{
public:
    explicit PlayableCharacter(ResourceManager &resources, float x = 0, float y = 0, int HP = 10, int m = 0,
                               float movespeed = 150, float manaregen = 2);
    bool isAnimationLocked() const;
    void setAnimationLock(bool lock);
    bool isAnimationPlaying();
    void update(const float &dt);
    void render(sf::RenderTarget& target) override;
    void setPosition(float x, float y);
    const sf::Vector2f& getPrevPos();
    void move(float x,float y);
    bool isAttacking() const;
    Hitbox& getDamageHitbox();
    sf::Vector2f getPosition();
    ~PlayableCharacter() override;
private:
    bool animationLock;
    bool hardLock;
    AnimationName animation;
    AnimationName lockAnimation;
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
