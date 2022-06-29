//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ANIMATION_H
#define PROGETTO_PROGRAMMAZIONE_ANIMATION_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
enum class AnimationName{KNIGHT_ATTACK,KNIGHT_IDLE,KNIGHT_ROLL,KNIGHT_DEATH,KNIGHT_RUN,SKELETON_MOVE,SKELETON_DEATH,SLIME_MOVE,
        SLIME_DEATH};
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
