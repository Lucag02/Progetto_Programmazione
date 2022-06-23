//
// Created by luca on 21/06/22.
//

#include "ResourceManager.h"
void ResourceManager::playAnimation(const std::string& name,const float& dt,sf::Sprite& sprite) {
    if(sprite.getTexture()!=&textures.at(name))
        sprite.setTexture(textures.at(name));
    animations.at(name).play(dt,sprite);
}
void ResourceManager::addTexture(const std::string& name,const std::string& filepath) {
    if(!textures[name].loadFromFile(filepath))
        //TODO add exception handling
        std::cout<<"could not load texture"<<"\n";
}
const sf::Texture* ResourceManager::getTexture(const std::string& name) const{
    return &textures.at(name);
}

void
ResourceManager::addAnimation(const std::string &AnimationName, int width,
                              int height, int startX, int startY, int endX,
                              int endY,float animationTimer) {
    animations.insert({AnimationName, Animation(startX, startY, endX, endY, width, height,
                                                textures.at(AnimationName), animationTimer)});
}

const Animation &ResourceManager::getAnimation(const std::string &animationName) {
    return animations.at(animationName);
}
