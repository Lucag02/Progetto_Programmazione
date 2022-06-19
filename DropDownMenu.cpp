//
// Created by luca on 19/06/22.
//

#include "DropDownMenu.h"

DropDownMenu::DropDownMenu(float x, float y, float width, float height, const std::string &title, sf::Font &font,
                           int elements, Type type) :
    x(x),y(y),width(width),height(height),numElements(elements),font(font),type(type){
    BTN=std::make_unique<Button>(x,y,width,height,title,font);
    open=false;
}

void DropDownMenu::update(const float &dt, const sf::Vector2f &mousePos) {
    BTN->update(mousePos);
}

void DropDownMenu::render(sf::RenderTarget &target) {
    if(!open)
        BTN->render(target);
}
