//
// Created by luca on 05/07/22.
//

#include "Projectile.h"
const float Projectile::projectileSpeed=300;
Projectile::Projectile(const ResourceManager &resources, sf::Vector2f mousePos, float x, float y) :
            resources(resources),exploded(false),erase(false) {
    direction.x=mousePos.x-x;
    direction.y=mousePos.y-y;
    float hypotenuse=sqrt(pow(direction.x,2)+pow(direction.y,2));
    direction.y=direction.y/hypotenuse;
    direction.x=direction.x/hypotenuse;
    float angle=atan(direction.y/direction.x);
    angle=(angle/6.28)*360;
    //sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setRotation(angle);
    sprite.setPosition(x,y);
    sprite.setTexture(resources.getTexture("PROJECTILE"));
    if(direction.x<0)
        sprite.setScale(-1,1);
    //FIXME find a better solution
    sprite.setTextureRect(sf::IntRect(0,0,32,32));
    hitbox=std::make_unique<Hitbox>(sprite,32,32,true);
    if(direction.x<0)
        hitbox->setScale(-1,1);
    hitbox->setRotation(angle);

}

void Projectile::update(const float &dt) {
    if(!exploded) {
        sprite.move(direction * dt * projectileSpeed);
        hitbox->move(direction * dt * projectileSpeed);
        resources.playAnimation(AnimationName::MOVE, dt, sprite);
    }
    else {
        resources.playAnimation(AnimationName::EXPLOSION, dt, sprite);
        if(!resources.getAnimation(AnimationName::EXPLOSION).isPlaying())
            erase=true;
    }
}

void Projectile::render(sf::RenderTarget &target) {
    target.draw(sprite);
}

void Projectile::explode() {
    exploded=true;
}

Hitbox &Projectile::getHitbox() {
    return *hitbox;
}

bool Projectile::canErase() const {
    return erase;
}
