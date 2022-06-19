//
// Created by luca on 19/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_STATES_H
#define PROGETTO_PROGRAMMAZIONE_STATES_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stack>

class States {
protected:
    sf::Vector2f mousePos;
    sf::RenderWindow* window;
    std::stack<std::unique_ptr<States>>* states;

public:
    void updateMousePos();
    virtual void update(const float& dt)=0;
    virtual void render(sf::RenderTarget &target)=0;
    virtual ~States()=default;
};

#endif //PROGETTO_PROGRAMMAZIONE_STATES_H
