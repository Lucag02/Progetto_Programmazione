//
// Created by luca on 19/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_DROPDOWNMENU_H
#define PROGETTO_PROGRAMMAZIONE_DROPDOWNMENU_H
#include "Button.h"
enum Type{RESOLUTION};
class DropDownMenu {
public:
    DropDownMenu(float x, float y, float width, float height, const std::string &title, sf::Font &font,
                 int elements, Type type);
    void update(const float &dt, const sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);
private:
    bool open;
    float x;
    float y;
    float height;
    float width;
    int numElements;
    sf::Font &font;
    Type type;
    std::unique_ptr<Button> BTN;
};


#endif //PROGETTO_PROGRAMMAZIONE_DROPDOWNMENU_H
