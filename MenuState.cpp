//
// Created by luca on 19/06/22.
//

#include "MenuState.h"
MenuState::MenuState(std::stack<std::unique_ptr<States>>* states, sf::RenderWindow* w){
    window=w;
    background.setSize(sf::Vector2f(800,450));
    if(!backgroundTexture.loadFromFile("../Resources/background.jpeg"))
        std::cout<<"couldn't load background.jpeg"<<"\n";
    background.setTexture(&backgroundTexture);
    if(!font.loadFromFile("../Config/ComicSans.ttf"))
    {
        std::cout<<"couldn't load ComicSans.ttf"<<"\n";
    }
    newGameBTN=std::make_unique<Button>(325.f,150.f,150.f,50.f,"New Game",font);
    optionsBTN=std::make_unique<Button>(325.f,250.f,150.f,50.f,"Options",font);
    quitBTN=std::make_unique<Button>(325.f,350.f,150.f,50.f,"QUIT",font);

    this->states=states;
}

void MenuState::update(const float &dt) {
    updateMousePos();
    newGameBTN->update(mousePos);
    quitBTN->update(mousePos);
    optionsBTN->update(mousePos);
    if(optionsBTN->isPressed()) {
        states->push(std::make_unique<OptionState>(states,window));
    }
    if(quitBTN->isPressed()) {
        window->close();
    }
}

void MenuState::render(sf::RenderTarget &target) {
    target.draw(background);
    newGameBTN->render(target);
    quitBTN->render(target);
    optionsBTN->render(target);
}

MenuState::~MenuState()=default;
