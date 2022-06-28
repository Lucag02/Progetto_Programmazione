//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ANIMATION_H
#define PROGETTO_PROGRAMMAZIONE_ANIMATION_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//TODO add enum class (instead of strings)
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
public:
    Animation(int startX, int startY, int endX, int endY, int widthOfFrame, int heightOfFrame, float animationTimer);
    void play(const float &dt, sf::Sprite &sprite);
    bool isPlaying() const;
    int getAnimationFrame() const;
};


#endif //PROGETTO_PROGRAMMAZIONE_ANIMATION_H
