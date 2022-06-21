//
// Created by luca on 20/06/22.
//

#include "Checkbox.h"
#include "Button.h"

Checkbox::Checkbox() {

}

Checkbox::Checkbox(float x, float y, float size, bool checked) : checked(checked),timer(0) {
    this->setPosition(x,y);
    this->setOutlineThickness(8);
    this->setOutlineColor(sf::Color(210,70,70));
    this->setSize(sf::Vector2f(size,size));
    if(!checkTexture.loadFromFile("../Resources/check.png"))
        std::cout<<"Could not load texture"<<"\n";
    this->setTexture(&checkTexture);
}

bool Checkbox::isChecked() const {
    return checked;
}

void Checkbox::update(const sf::Vector2f &mousePos, const float &dt) {
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
        timer=0;
    }
}

void Checkbox::render(sf::RenderTarget &target) {
    target.draw(*this);
}