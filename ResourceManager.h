//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_RESOURCEMANAGER_H
#define PROGETTO_PROGRAMMAZIONE_RESOURCEMANAGER_H
#include <iostream>
#include <memory>
#include "Animation.h"

class ResourceManager {
private:
    std::shared_ptr<std::map<std::string,sf::Texture>> textures;
    std::map<std::string,Animation> animations;
public:
    ResourceManager();
    void addTexture(const std::string& name,const std::string& filepath);
    const sf::Texture& getTexture(const std::string& name) const;
    void addAnimation(const std::string &AnimationName, int width, int height, int startX, int startY, int endX,
                      int endY, float animationTimer);
    void playAnimation(const std::string& name, const float& dt,sf::Sprite& sprite);
    const Animation & getAnimation(const std::string& animationName);
};

#endif //PROGETTO_PROGRAMMAZIONE_RESOURCEMANAGER_H