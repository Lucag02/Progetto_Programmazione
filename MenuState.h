//
// Created by luca on 19/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_MENUSTATE_H
#define PROGETTO_PROGRAMMAZIONE_MENUSTATE_H

#include <iostream>
#include "States.h"
#include "Button.h"
#include "DropDownMenu.h"
class MenuState: public States{
private:
    std::unique_ptr<DropDownMenu> resolutionDDM;
    std::unique_ptr<Button> newGameBTN;
    std::unique_ptr<Button> quitBTN;
    std::unique_ptr<Button> optionsBTN;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;
public:
    MenuState(std::stack<std::unique_ptr<States>>* states, sf::RenderWindow* w);
    void update(const float& dt) override;
    void render(sf::RenderTarget &target) override;
    ~MenuState() override;
};


#endif //PROGETTO_PROGRAMMAZIONE_MENUSTATE_H
