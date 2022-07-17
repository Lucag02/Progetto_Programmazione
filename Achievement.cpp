//
// Created by luca on 16/07/22.
//

#include "Achievement.h"
const float Achievement::timeOnScreen=1;
const int Achievement::killRequired=1;
const int Achievement::spellsRequired=1;
Achievement::Achievement(const sf::Font &font, Subject *subject)
        : font(font), subject(subject), unlocked(false), timer(0),spellUnlocked(false),killsUnlocked(false){
    subject->registerObserver(this);
    container.setFillColor(sf::Color::Black);
    container.setSize(sf::Vector2f(250,60));
    biggerText.setFont(font);
    biggerText.setFillColor(sf::Color::White);
    biggerText.setCharacterSize(20);
    biggerText.setString("Achievement Unlocked!");
    smallerText.setFont(font);
    smallerText.setFillColor(sf::Color::White);
    smallerText.setCharacterSize(15);
}

void Achievement::update(const float &dt, sf::Vector2f viewPos, int kills, int spells) {
    if(unlocked) {
        timer+=dt;
        container.setPosition(viewPos.x+800-container.getSize().x,viewPos.y+450-container.getSize().y);
        biggerText.setPosition(container.getPosition().x+5,container.getPosition().y+5);
        smallerText.setPosition(biggerText.getPosition().x+5,biggerText.getPosition().y+biggerText.getCharacterSize()+5);
        if(timer> timeOnScreen)
            unlocked = false;
    }
    if(!unlocked) {
        if (kills >= killRequired&&!killsUnlocked) {
            timer = 0;
            unlocked = true;
            killsUnlocked=true;
            smallerText.setString("Monster Slayer");
        }
        if (spells >= spellsRequired&&!spellUnlocked) {
            timer = 0;
            unlocked = true;
            spellUnlocked=true;
            smallerText.setString("Mage");
        }
    }
}

void Achievement::render(sf::RenderTarget &target) {
    if(unlocked){
        target.draw(container);
        target.draw(biggerText);
        target.draw(smallerText);
    }
}

Achievement::~Achievement() {
    subject->removeObservers(this);
}
