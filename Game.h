//
// Created by luca on 19/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAME_H
#define PROGETTO_PROGRAMMAZIONE_GAME_H


#include<fstream>
#include"MenuState.h"
class Game {
public:
    Game();

    void checkEvent();

    void run();

    void initWindow();

    ~Game();

private:
    sf::RenderWindow* window;
    std::stack <std::unique_ptr<States>> states;
    sf::Event event;
    sf::Clock clock;
    float dt;
};


#endif //PROGETTO_PROGRAMMAZIONE_GAME_H
