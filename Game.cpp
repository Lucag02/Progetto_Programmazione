//
// Created by luca on 19/06/22.
//

#include "Game.h"
Game::Game() {
    initWindow();
    dt=0;
}
void Game::run() {
    states.push(std::make_unique<MenuState>(&states,window));
    while (window->isOpen()) {
        clock.restart();
        checkEvent();
        if (!states.empty()) {
            window->clear();
            states.top()->update(dt);
            states.top()->render(*window);
            window->display();
            dt = clock.getElapsedTime().asSeconds();
            //std::cout<<dt<<"\n";
        } else
            window->close();
    }
}

void Game::initWindow() {
    std::ifstream ifs("../Config/window.ini");
    std::string title = "COMclone";
    sf::VideoMode windowBounds=sf::VideoMode::getDesktopMode();
    unsigned framerateLimit = 144;
    bool vsync = true;
    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> windowBounds.width >> windowBounds.height;
        ifs >> framerateLimit;
        ifs >> vsync;
    }
    ifs.close();
    window = new sf::RenderWindow(sf::VideoMode(windowBounds), title);
    //window->setSize(sf::Vector2u(1600,900));
    window->setFramerateLimit(framerateLimit);
    window->setVerticalSyncEnabled(vsync);
}

Game::~Game() {
    delete window;
    while (!states.empty())
    {
        states.pop();
    }
}

void Game::checkEvent() {
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    states.pop();
            }
        if(event.type==sf::Event::Closed)
            window->close();
    }
}
