//
// Created by luca on 19/06/22.
//

#include "DropDownMenu.h"


DropDownMenu::DropDownMenu(float x, float y, float width, float height, const std::string &title,
                           sf::Font &font, std::vector<std::string> list) :
        x(x), y(y), width(width), height(height), font(font), time(0),
        activeBTN(x, y, width, height, title, font), open(false), titleList(std::move(list)) {
    for (int i = 0; i != titleList.size(); i++)
        buttonList.emplace_back(x, this->y + i * height, width, height, titleList[i], font);
}

void DropDownMenu::update(const sf::Vector2f &mousePos, const float &dt) {
    time += dt;
    activeBTN.update(mousePos);

    if (!open) {
        if (activeBTN.isPressed() && time > 0.3) {
            open = true;
            time = 0;
        }
    } else
        for (int i = 0; i != buttonList.size(); i++) {
            buttonList[i].update(mousePos);
            if (buttonList[i].isPressed() && time > 0.3) {
                activeBTN.setText(buttonList[i].getText());
                activeBTN.setTextPos(buttonList[i].getTextPos().x, buttonList[i].getTextPos().y - height * i);
                open = false;
                time = 0;
            }

        }

}


void DropDownMenu::render(sf::RenderTarget &target) {
    if (!open)
        activeBTN.render(target);
    else
        for (auto &i: buttonList)
            i.render(target);

}

std::string DropDownMenu::getActiveString() const {
    return activeBTN.getText().getString();
}
