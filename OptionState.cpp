//
// Created by luca on 20/06/22.
//

#include "OptionState.h"


OptionState::OptionState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) {
    window=w;
    this->states=states;
    if(!font.loadFromFile("../Config/ComicSans.ttf"))
    {
        std::cout<<"couldn't load ComicSans.ttf"<<"\n";
    }
    std::string title=std::to_string(window->getSize().x)+" x "+std::to_string(window->getSize().y);
    std::vector<std::string> titleList={"1920 x 1080", "1600 x 900","800 x 450"};
    resolutionDDM=std::make_unique<DropDownMenu>(325.f,250.f,150.f,50.f,title,font,titleList);
}

void OptionState::update(const float &dt) {
    updateMousePos();
    resolutionDDM->update(mousePos,dt);
}

void OptionState::render(sf::RenderTarget &target) {
    resolutionDDM->render(target);
}
