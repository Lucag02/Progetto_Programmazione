//
// Created by luca on 19/06/22.
//

#include "Button.h"

#include <utility>
Button::Button(float x, float y, float width, float height, const std::string& title, const sf::Font &font) {
    button.setPosition(sf::Vector2f(x,y));
    button.setSize(sf::Vector2f(width,height));
    text.setString(title);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(button.getPosition().x+(button.getGlobalBounds().width/2)-text.getGlobalBounds().width/2.f,
                     button.getPosition().y+(button.getGlobalBounds().height/2)-text.getGlobalBounds().height/2.f);
    button.setFillColor(sf::Color(200,200,200,100));
    btnState=IDLE;
}
void::Button::update(const sf::Vector2f& mousePos)
{
    btnState=IDLE;
    button.setFillColor(sf::Color(200,200,200,100));
    if(button.getGlobalBounds().contains(mousePos))
    {
        btnState=HOVER;
        button.setFillColor(sf::Color(50,50,50,100));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            btnState = PRESSED;
            button.setFillColor(sf::Color(40,40,40,150));
        }
    }
}
void Button::render(sf::RenderTarget &target) {
    target.draw(button);
    target.draw(text);
}
bool Button::isPressed() {
    if(btnState==PRESSED)
        return true;
    return false;
}

void Button::setText(const sf::Text &title) {
    text=title;
}

sf::Text Button::getText() {
    return text;
}

void Button::setTextPos(float x, float y) {
    text.setPosition(x,y);
}

const sf::Vector2f &Button::getTextPos() {
    return text.getPosition();
}







