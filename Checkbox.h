//
// Created by luca on 20/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_CHECKBOX_H
#define PROGETTO_PROGRAMMAZIONE_CHECKBOX_H
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Checkbox:public sf::RectangleShape {
private:
    bool checked;
    float timer;
    sf::Texture checkTexture;
public:
    Checkbox();
    Checkbox(float x, float y, float size, bool checked = false);
    bool isChecked() const;
    void update(const sf::Vector2f &mousePos, const float &dt);
    void render(sf::RenderTarget& target);
};


#endif //PROGETTO_PROGRAMMAZIONE_CHECKBOX_H
