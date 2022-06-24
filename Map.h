//
// Created by luca on 24/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_MAP_H
#define PROGETTO_PROGRAMMAZIONE_MAP_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "PlayableCharacter.h"
#include "Enemy.h"
class Map {
private:
    class Room {
    public:
        Room(int width,int height,int x, int y);
        sf::Vector2i getCenter() const;
        bool intersects (const Room& otherRoom) const;
    private:
        sf::Vector2i topLeftCoordinates;
        int width;
        int height;
    };
    int roomQuantity;
    int tileWidth;
    int tileHeight;
    const sf::Texture& texture;
    std::vector<Room> rooms;
    std::map<std::string, sf::IntRect> tiles;
    std::vector<std::vector<sf::RectangleShape>> map;
    int sizeX;
    int sizeY;
    std::vector<Enemy>& enemies;
    PlayableCharacter& player;
public:
    explicit Map(const sf::Texture &texture, PlayableCharacter &player, std::vector<Enemy> & enemies);
    void update();
    void render(sf::RenderTarget &target);
    void createMap();
    void placeRooms();
    void createCorridors(const Room &room1, const Room &room2);
};

#endif //PROGETTO_PROGRAMMAZIONE_MAP_H
