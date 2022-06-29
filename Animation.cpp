//
// Created by luca on 21/06/22.
//

#include "Animation.h"
Animation::Animation(int startX, int startY, int endX, int endY, int widthOfFrame, int heightOfFrame,
                     float animationTimer,
                     bool repeatable) :
        startRect(sf::IntRect(startX*widthOfFrame, startY*heightOfFrame,
                              widthOfFrame, heightOfFrame)),
        endRect(sf::IntRect(endX*widthOfFrame, endY*heightOfFrame,
                            widthOfFrame, heightOfFrame)),
        currentRect(startRect), animationTimer(animationTimer),
        width(widthOfFrame), height(heightOfFrame),timer(0),playing(!repeatable),repeatable(repeatable){
}

void Animation::play(const float &dt, sf::Sprite &sprite){
    timer += 1000 * dt;
    if(timer>=animationTimer)
    {
        timer-=animationTimer;
        if(currentRect!=endRect) {
            playing=true;
            //FIXME
            if (currentRect.left == endRect.left) {
                currentRect.top += height;
                currentRect.left = 0;
            } else
                currentRect.left += width;
        }
        else {
            playing=false;
            currentRect = startRect;
        }
        if(playing||repeatable)
            sprite.setTextureRect(currentRect);
    }
}

bool Animation::isPlaying() const {
    return playing;
}

int Animation::getAnimationFrame() const {
    if(currentRect.top==startRect.top)
        return (currentRect.left-startRect.left)/width;
    else
        return (endRect.left*(currentRect.top-startRect.top-height)+endRect.left-startRect.left+currentRect.left)/width;
}


