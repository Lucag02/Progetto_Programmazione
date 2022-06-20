//
// Created by luca on 20/06/22.
//

#include "Checkbox.h"
#include "Button.h"

Checkbox::Checkbox() {

}

Checkbox::Checkbox(float x, float y) : checked(true), pressed(false), timer(0) {
    this->setPosition(x,y);
    this->setOutlineThickness(8);
    this->setOutlineColor(sf::Color(210,70,70));
    this->setSize(sf::Vector2f(50,50));
    if(!checkTexture.loadFromFile("../Resources/check.png"))
        std::cout<<"Could not load texture"<<"\n";
    this->setTexture(&checkTexture);
}

bool Checkbox::isPressed() const {
    return pressed;
}

void Checkbox::update(const sf::Vector2f &mousePos, const float &dt) {
    pressed=false;
    timer+=dt;
    if(checked) {
        this->setTexture(&checkTexture);
        this->setFillColor(sf::Color::White);
    }
    else {
        this->setTexture(nullptr);
        this->setFillColor(sf::Color::Transparent);
    }
    if(timer>0.3&&this->getGlobalBounds().contains(mousePos)&&sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        checked = (checked + 1) % 2;
        pressed = true;
        timer=0;
    }
}

void Checkbox::render(sf::RenderTarget &target) {
    target.draw(*this);
}