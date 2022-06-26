//
// Created by luca on 21/06/22.
//
#include "ResourceManager.h"
ResourceManager::ResourceManager():textures(std::make_shared<std::map<std::string,sf::Texture>>()) {
}
void ResourceManager::playAnimation(const std::string& name,const float& dt,sf::Sprite& sprite) {
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
ResourceManager::addAnimation(const std::string &AnimationName, int width,
                              int height, int startX, int startY, int endX,
                              int endY,float animationTimer) {
    animations.insert({AnimationName, Animation(startX, startY, endX, endY, width, height,
                                                textures->at(AnimationName), animationTimer)});
}

const Animation & ResourceManager::getAnimation(const std::string &animationName) {
    return animations.at(animationName);
}
