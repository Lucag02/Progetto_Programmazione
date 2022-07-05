//
// Created by luca on 05/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PROJECTILE_H
#define PROGETTO_PROGRAMMAZIONE_PROJECTILE_H
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
class Projectile {
private:
    sf::Sprite sprite;
    sf::Sprite explosion;
    ResourceManager resources;
    sf::Vector2f direction;
    const static float projectileSpeed;
    bool exploded;
public:
    Projectile(const ResourceManager &resources, sf::Vector2f mousePos, float x, float y);
    void update(const float& dt);
    void render(sf::RenderTarget& target);
    void explode();
};


#endif //PROGETTO_PROGRAMMAZIONE_PROJECTILE_H
