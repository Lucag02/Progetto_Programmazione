//
// Created by luca on 21/06/22.
//

#include "Animation.h"
Animation::Animation(int startX, int startY, int endX, int endY, int widthOfFrame, int heightOfFrame,
                     sf::Texture &texture, float animationTimer) :
        startRect(sf::IntRect(startX*widthOfFrame, startY*heightOfFrame,
                              widthOfFrame, heightOfFrame)),
        endRect(sf::IntRect(endX*widthOfFrame, endY*heightOfFrame,
                            widthOfFrame, heightOfFrame)),
        currentRect(startRect), timer(0), animationTimer(animationTimer),
        width(widthOfFrame), height(heightOfFrame){}

void Animation::play(const float &dt, sf::Sprite &sprite){
    timer+=1000*dt;
    if(timer>=animationTimer)
    {
        timer-=animationTimer;
        if(currentRect!=endRect)
            currentRect.left += width;
        else
            currentRect.left = startRect.left;
        sprite.setTextureRect(currentRect);
    }
}
bool Animation::isPlaying() const {
    if (currentRect.left == startRect.left)
        return false;
    return true;
}