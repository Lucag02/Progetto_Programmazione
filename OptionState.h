//
// Created by luca on 20/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_OPTIONSTATE_H
#define PROGETTO_PROGRAMMAZIONE_OPTIONSTATE_H

#include <iostream>
#include "DropDownMenu.h"
#include "States.h"
#include "Checkbox.h"
class OptionState:public States {
private:
    std::unique_ptr<DropDownMenu> resolutionDDM;
    sf::Font font;
    sf::Text resolution;
    sf::Text fullscreen;
    sf::Text vsync;
    Checkbox vsyncCB;
    Checkbox fullscreenCB;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
public:
    OptionState(std::stack<std::unique_ptr<States>>* states, sf::RenderWindow* w);
    void update(const float& dt) override;
    void render(sf::RenderTarget& target) override;
};


#endif //PROGETTO_PROGRAMMAZIONE_OPTIONSTATE_H
