//
// Created by luca on 19/06/22.
//

#include "States.h"

void States::updateMousePos() {
    mousePos=window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}
