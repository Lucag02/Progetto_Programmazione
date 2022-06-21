//
// Created by luca on 19/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_DROPDOWNMENU_H
#define PROGETTO_PROGRAMMAZIONE_DROPDOWNMENU_H
#include "Button.h"
class DropDownMenu {
public:
    DropDownMenu(float x, float y, float width, float height, const std::string &title, sf::Font &font,
                 std::vector<std::string> list);
    void update(const sf::Vector2f &mousePos, const float &dt);
    void render(sf::RenderTarget &target);
    std::string getActiveString();
private:
    bool open;
    float x;
    float y;
    float height;
    float width;
    float time;
    sf::Font &font;
    std::vector<std::string> titleList;
    std::vector<Button> buttonList;
    Button activeBTN;
};


#endif //PROGETTO_PROGRAMMAZIONE_DROPDOWNMENU_H
