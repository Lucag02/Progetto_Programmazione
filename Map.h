//
// Created by luca on 24/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_MAP_H
#define PROGETTO_PROGRAMMAZIONE_MAP_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>
#include "PlayableCharacter.h"
#include "Enemy.h"
class Map {
private:
    struct Tile{
        sf::RectangleShape tile;
        float distance=900;
        explicit Tile(sf::RectangleShape  rectangle):tile(std::move(rectangle)){};
    };
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
    std::vector<std::vector<Tile>> map;
    int sizeX;
    int sizeY;
    std::vector<std::unique_ptr<Enemy>>& enemies;
    PlayableCharacter& player;
    ResourceManager& enemyResources;
    float distanceFromPlayer(float x, float y);
public:
    Map(const sf::Texture &texture, ResourceManager &enemyResources, PlayableCharacter &player,
                 std::vector<std::unique_ptr<Enemy>> &enemies);
    void update(const float &dt);
    void render(sf::RenderTarget &target);
    void createMap();
    void placeRooms();
    void createCorridors(const Room &room1, const Room &room2);
    sf::Vector2i getDiredctionToPlayer(float x, float y);
};

#endif //PROGETTO_PROGRAMMAZIONE_MAP_H
