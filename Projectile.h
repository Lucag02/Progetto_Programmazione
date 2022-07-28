//
// Created by luca on 05/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PROJECTILE_H
#define PROGETTO_PROGRAMMAZIONE_PROJECTILE_H
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Hitbox.h"
class Projectile {
private:
    sf::Sprite sprite;
    ResourceManager resources;
    sf::Vector2f direction;
    const static float projectileSpeed;
    bool exploded;
    std::unique_ptr<Hitbox> hitbox;
    bool erase;
public:
    Projectile(const ResourceManager &resources, sf::Vector2f mousePos, float x, float y);
    void update(const float& dt);
    void render(sf::RenderTarget& target);
    Hitbox& getHitbox() const;
    void explode();
    bool canErase() const;
};


#endif //PROGETTO_PROGRAMMAZIONE_PROJECTILE_H
