//
// Created by luca on 16/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ACHIEVEMENT_H
#define PROGETTO_PROGRAMMAZIONE_ACHIEVEMENT_H
#include "Observer.h"
#include "Subject.h"
class Achievement :public Observer{
private:
    const sf::Font& font;
    Subject* subject;
    const static float timeOnScreen;
    const static int killRequired;
    const static int spellsRequired;
    float timer;
    bool unlocked;
    sf::RectangleShape container;
    sf::Text biggerText;
    sf::Text smallerText;
    bool killsUnlocked;
    bool spellUnlocked;
public:
    explicit Achievement(const sf::Font &font, Subject *subject);
    void update(const float &dt, sf::Vector2f viewPos, int kills, int spells) override;
    void render(sf::RenderTarget& target) override;
    ~Achievement() override;
};


#endif //PROGETTO_PROGRAMMAZIONE_ACHIEVEMENT_H
