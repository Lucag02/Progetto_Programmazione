//
// Created by luca on 09/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_CHARACTERSELECTIONSTATE_H
#define PROGETTO_PROGRAMMAZIONE_CHARACTERSELECTIONSTATE_H
#include "GameState.h"
class CharacterSelectionState: public States {
private:
    sf::RectangleShape mage;
    sf::RectangleShape knight;
    sf::Texture mageTexture;
    sf::Texture knightTexture;
    sf::Texture backgroundTexture;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape background;
public:
    CharacterSelectionState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w);
    void update(const float &dt) override;
    void render(sf::RenderTarget& target) override;
};


#endif //PROGETTO_PROGRAMMAZIONE_CHARACTERSELECTIONSTATE_H
