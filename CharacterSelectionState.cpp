//
// Created by luca on 09/07/22.
//

#include "CharacterSelectionState.h"

CharacterSelectionState::CharacterSelectionState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) {
    this->states=states;
    window=w;
    if(!mageTexture.loadFromFile("../Resources/Mage_selection.png")||
        !knightTexture.loadFromFile("../Resources/Knight_selection.png")||
        !backgroundTexture.loadFromFile("../Resources/background.jpeg"))
        std::cerr<<"could not load texture";
    if(!font.loadFromFile("../Config/ComicSans.ttf"))
        std::cerr<<"could not load font";
    background.setTexture(&backgroundTexture);
    mage.setTexture(&mageTexture);
    knight.setTexture(&knightTexture);
    background.setSize(window->getView().getSize());
    text.setFont(font);
    text.setPosition(50,30);
    text.setFillColor(sf::Color::White);
    text.setString("CHOOSE YOUR CHARACTER");
    text.setCharacterSize(50);
    mage.setPosition(100,150);
    mage.setSize(sf::Vector2f(200,250));
    mage.setOutlineColor(sf::Color::White);
    mage.setOutlineThickness(2);
    knight.setPosition(500,150);
    knight.setSize(sf::Vector2f(200,250));
    knight.setOutlineColor(sf::Color::White);
    knight.setOutlineThickness(2);
}

void CharacterSelectionState::update(const float &dt) {
    mage.setFillColor(sf::Color::White);
    knight.setFillColor(sf::Color::White);
    updateMousePos();
    if(mage.getGlobalBounds().contains(mousePos)) {
        mage.setFillColor(sf::Color(200, 200, 200));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mage.setFillColor(sf::Color(150, 150, 150));
            states->push(std::make_unique<GameState>(states,window,MAGE));
        }

    }
    else {
        if (knight.getGlobalBounds().contains(mousePos)) {
            knight.setFillColor(sf::Color(200, 200, 200));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                knight.setFillColor(sf::Color(150, 150, 150));
                states->push(std::make_unique<GameState>(states,window,KNIGHT));
            }
        }
    }
}

void CharacterSelectionState::render(sf::RenderTarget &target) {
    target.draw(background);
    target.draw(mage);
    target.draw(knight);
    target.draw(text);
}
