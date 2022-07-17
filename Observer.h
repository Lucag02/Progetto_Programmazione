//
// Created by luca on 16/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_OBSERVER_H
#define PROGETTO_PROGRAMMAZIONE_OBSERVER_H
#include <SFML/Graphics.hpp>
class Observer {
public:
    virtual void update(const float &dt, sf::Vector2f viewPos, int kills, int spells) =0;
    virtual void render(sf::RenderTarget& target)=0;
    virtual ~Observer()=default;
};
#endif //PROGETTO_PROGRAMMAZIONE_OBSERVER_H
