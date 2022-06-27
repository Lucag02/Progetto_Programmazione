//
// Created by luca on 21/06/22.
//

#include "Animation.h"
Animation::Animation(int startX, int startY, int endX, int endY, int widthOfFrame, int heightOfFrame,
                     const sf::Texture &texture, float animationTimer) :texture(texture),
        startRect(sf::IntRect(startX*widthOfFrame, startY*heightOfFrame,
                              widthOfFrame, heightOfFrame)),
        endRect(sf::IntRect(endX*widthOfFrame, endY*heightOfFrame,
                            widthOfFrame, heightOfFrame)),
        currentRect(startRect), animationTimer(animationTimer),
        width(widthOfFrame), height(heightOfFrame),timer(0){
}

void Animation::play(const float &dt, sf::Sprite &sprite){
    timer += 1000 * dt;
    if(timer>=animationTimer)
    {
        timer-=animationTimer;
        if(currentRect!=endRect)
            if(currentRect.left==endRect.left) {
                currentRect.top += height;
                currentRect.left = 0;
            }
            else
                currentRect.left += width;
        else
            currentRect = startRect;
        sprite.setTextureRect(currentRect);
    }
}
bool Animation::isPlaying() const {
    if (currentRect.left == startRect.left)
        return false;
    return true;
}


