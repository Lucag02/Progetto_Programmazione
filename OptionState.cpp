//
// Created by luca on 20/06/22.
//

#include "OptionState.h"


OptionState::OptionState(std::stack<std::unique_ptr<States>> *states, sf::RenderWindow *w) {
    window=w;
    this->states=states;
    background.setSize(sf::Vector2f(800.f,450.f));
    if(!backgroundTexture.loadFromFile("../Resources/background.jpeg"))
        std::cout<<"couldn't load background.jpeg"<<"\n";
    background.setTexture(&backgroundTexture);
    if(!font.loadFromFile("../Config/ComicSans.ttf"))
    {
        std::cout<<"couldn't load ComicSans.ttf"<<"\n";
    }
    vsyncText.setFont(font);
    resolutionText.setFont(font);
    vsyncText.setString("Vsync");
    resolutionText.setString("Resolution");
    vsyncText.setFillColor(sf::Color::White);
    resolutionText.setFillColor(sf::Color::White);
    resolutionText.setCharacterSize(40);
    vsyncText.setCharacterSize(40);
    vsyncText.setPosition(200.f, 125.f);
    resolutionText.setPosition(200.f, 275.f);
    apply=std::make_unique<Button>(350,375,100,40,"Apply",font);
    back=std::make_unique<Button>(30,375,100,40,"Back",font);
    file=std::fstream ("../Config/window.ini");
    goToLine(file,2);
    std::string title,tmp;
    file>>title;
    title=title+" x ";
    file>>tmp;
    title.append(tmp);
    std::vector<std::string> titleList={"1920 x 1080", "1600 x 900","800 x 450"};
    resolutionDDM=std::make_unique<DropDownMenu>(450.f,275.f,150.f,50.f,title,font,titleList);
    bool checked;
    goToLine(file,4);
    file>>checked;
    vsyncCB= Checkbox(500.f, 125.f, 50, checked);
}

void OptionState::update(const float &dt) {
    updateMousePos();
    apply->update(mousePos);
    back->update(mousePos);
    resolutionDDM->update(mousePos,dt);
    vsyncCB.update(mousePos, dt);
    if(apply->isPressed()){
        goToLine(file, 4);
        if(vsyncCB.isChecked()) {
            file << "1";
            window->setVerticalSyncEnabled(true);
        }
        else {
            file << "0";
            window->setVerticalSyncEnabled(false);
        }
        goToLine(file,2);
        std::string tmp=resolutionDDM->getActiveString();
        tmp.resize(11,' ');
        file<<tmp.replace(tmp.find(" x"),3," ");
        window->setSize(sf::Vector2u(std::stoi(tmp.substr(0,4)),std::stoi(tmp.substr(4,tmp.size()-4))));
    }
    if(back->isPressed())
        states->pop();
}

void OptionState::render(sf::RenderTarget &target) {
    target.draw(background);
    target.draw(resolutionText);
    target.draw(vsyncText);
    apply->render(target);
    back->render(target);
    vsyncCB.render(target);
    resolutionDDM->render(target);
}

OptionState::~OptionState() {
    if(file.is_open())
        file.close();
}

std::fstream& OptionState::goToLine(std::fstream &file, unsigned int num) {
    file.seekg(std::ios::beg);
    for(int i=0;i<num-1;i++)
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    return file;
}