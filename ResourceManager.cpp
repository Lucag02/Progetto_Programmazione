//
// Created by luca on 21/06/22.
//
#include "ResourceManager.h"
ResourceManager::ResourceManager():textures(std::make_shared<std::map<std::string,sf::Texture>>()) {
}
void ResourceManager::playAnimation(AnimationName name, const float& dt, sf::Sprite& sprite) {
    animations.at(name).play(dt,sprite);
}
void ResourceManager::addTexture(const std::string& name,const std::string& filepath) {
    if(!textures->operator[](name).loadFromFile(filepath))
        //TODO add exception handling
        std::cout<<"could not load texture"<<"\n";
}

const sf::Texture& ResourceManager::getTexture(const std::string& name) const{
    return textures->at(name);
}

void
ResourceManager::addAnimation(AnimationName animationName, int width, int height, int startX, int startY, int endX,
                              int endY,
                              float animationTimer, bool repeatable) {
    animations.insert({animationName, Animation(startX, startY, endX, endY, width, height, animationTimer, repeatable)});
}

const Animation & ResourceManager::getAnimation(AnimationName animationName) {
    return animations.at(animationName);
}
