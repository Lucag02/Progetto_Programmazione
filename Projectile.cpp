//
// Created by luca on 05/07/22.
//

#include "Projectile.h"
const float Projectile::projectileSpeed=300;
Projectile::Projectile(const ResourceManager &resources, sf::Vector2f mousePos, float x, float y) :
            resources(resources),exploded(false) {
    direction.x=mousePos.x-x;
    direction.y=mousePos.y-y;
    float hypotenuse=sqrt(direction.x*direction.x+direction.y+direction.y);
    direction.y=direction.y/hypotenuse;
    direction.x=direction.x/hypotenuse;
    sprite.setPosition(x,y);
    sprite.setTexture(resources.getTexture("PROJECTILE"));
    explosion.setTexture(resources.getTexture("EXPLOSION"));
    if(direction.x<0)
        sprite.setScale(-1,1);
    //FIXME find a better solution
    sprite.setTextureRect(sf::IntRect(0,0,32,32));

}

void Projectile::update(const float &dt) {
    if(!exploded) {
        sprite.move(direction * dt * projectileSpeed);
        resources.playAnimation(AnimationName::MOVE, dt, sprite);
    }
    else
        resources.playAnimation(AnimationName::EXPLOSION,dt,explosion);
}

void Projectile::render(sf::RenderTarget &target) {
    if(!exploded)
        target.draw(sprite);
    else
        target.draw(explosion);
}

void Projectile::explode() {
    exploded=true;
    explosion.setOrigin(sprite.getPosition());
    explosion.setPosition(sprite.getPosition());
}
