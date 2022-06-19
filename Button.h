//
// Created by luca on 19/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_BUTTON_H
#define PROGETTO_PROGRAMMAZIONE_BUTTON_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
enum buttonStates {IDLE,PRESSED,HOVER};
class Button {
private:
    sf::RectangleShape button;
    sf::Text text;
    buttonStates btnState;
public:
    Button(float x, float y, float width, float height, const std::string& title, const sf::Font &font);
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);
    bool isPressed();
};


#endif //PROGETTO_PROGRAMMAZIONE_BUTTON_H
