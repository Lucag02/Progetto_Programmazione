//
// Created by luca on 20/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_OPTIONSTATE_H
#define PROGETTO_PROGRAMMAZIONE_OPTIONSTATE_H
#include <string>
#include <fstream>
#include <limits>
#include <iostream>
#include "DropDownMenu.h"
#include "States.h"
#include "Checkbox.h"
class OptionState:public States {
private:
    std::unique_ptr<DropDownMenu> resolutionDDM;
    sf::Font font;
    sf::Text resolutionText;
    sf::Text vsyncText;
    Checkbox vsyncCB;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    std::unique_ptr<Button> apply;
    std::unique_ptr<Button> back;
    std::fstream file;
    static std::fstream & goToLine(std::fstream& file, unsigned int num);
public:
    OptionState(std::stack<std::unique_ptr<States>>* states, sf::RenderWindow* w);
    void update(const float& dt) override;
    void render(sf::RenderTarget& target) override;
    ~OptionState() override;
};


#endif //PROGETTO_PROGRAMMAZIONE_OPTIONSTATE_H
