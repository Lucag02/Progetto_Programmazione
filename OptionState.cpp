//
// Created by luca on 20/06/22.
//

#include "OptionState.h"


OptionState::OptionState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) {
    window=w;
    this->states=states;
    background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x),
                                    static_cast<float>(window->getSize().y)));
    if(!backgroundTexture.loadFromFile("../Resources/background.jpeg"))
        std::cout<<"couldn't load background.jpeg"<<"\n";
    background.setTexture(&backgroundTexture);
    if(!font.loadFromFile("../Config/ComicSans.ttf"))
    {
        std::cout<<"couldn't load ComicSans.ttf"<<"\n";
    }
    vsync.setFont(font);
    fullscreen.setFont(font);
    resolution.setFont(font);
    vsync.setString("Vsync");
    fullscreen.setString("Fullscreen");
    resolution.setString("Resolution");
    std::string title=std::to_string(window->getSize().x)+" x "+std::to_string(window->getSize().y);
    std::vector<std::string> titleList={"1920 x 1080", "1600 x 900","800 x 450"};
    resolutionDDM=std::make_unique<DropDownMenu>(325.f,150.f,150.f,50.f,title,font,titleList);
    vsyncCB= Checkbox(325.f, 250);
}

void OptionState::update(const float &dt) {
    updateMousePos();
    resolutionDDM->update(mousePos,dt);
    vsyncCB.update(mousePos, dt);
}

void OptionState::render(sf::RenderTarget &target) {
    target.draw(background);
    vsyncCB.render(target);
    resolutionDDM->render(target);
}
