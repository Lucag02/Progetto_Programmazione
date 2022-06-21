//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMESTATE_H
#define PROGETTO_PROGRAMMAZIONE_GAMESTATE_H
#include "States.h"
#include "PlayableCharacter.h"
class GameState: public States {
private:
    sf::View view;
    PlayableCharacter player;
public:
    GameState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow* w);
    void update(const float& dt) override;
    void render(sf::RenderTarget &target) override;
    ~GameState() override;
};



#endif //PROGETTO_PROGRAMMAZIONE_GAMESTATE_H