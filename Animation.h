//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ANIMATION_H
#define PROGETTO_PROGRAMMAZIONE_ANIMATION_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
enum class AnimationName{ATTACK=0,IDLE=1,ROLL=2,DEATH=3,MOVE=4,KNIGHT_ATTACK=10,KNIGHT_IDLE=11,KNIGHT_ROLL=12,KNIGHT_DEATH=13,
        KNIGHT_RUN=14,SKELETON_MOVE=44,SKELETON_ATTACK=40,SKELETON_DEATH=43,SLIME_MOVE=34,
        SLIME_DEATH=33,SLIME_ATTACK=30};
class Animation {
private:
    sf::IntRect startRect;
    sf::IntRect endRect;
    sf::IntRect currentRect;
    float timer;
    float animationTimer;
    int width;
    int height;
    bool playing;
    bool repeatable;
public:
    Animation(int startX, int startY, int endX, int endY, int widthOfFrame, int heightOfFrame, float animationTimer,
              bool repeatable=true);
    void play(const float &dt, sf::Sprite &sprite);
    bool isPlaying() const;
    int getAnimationFrame() const;
};


#endif //PROGETTO_PROGRAMMAZIONE_ANIMATION_H
