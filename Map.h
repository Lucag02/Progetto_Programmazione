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
    enum class TileType{VOID=0,WALL=1,TERRAIN=2,GRASS=3};
    struct Tile{
        TileType type=TileType::GRASS;
        sf::RectangleShape tile;
        float distance=900;
        explicit Tile(sf::RectangleShape  rectangle):tile(std::move(rectangle)){};
        void setTile(TileType tileType,const std::map<TileType, sf::IntRect>& t){
            tile.setTextureRect(t.at(tileType));
            type=tileType;
        }
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
    std::map<TileType, sf::IntRect> tiles;
    std::vector<std::vector<Tile>> map;
    int sizeX;
    int sizeY;
    std::vector<std::unique_ptr<Enemy>>& enemies;
    PlayableCharacter& player;
    std::vector<ResourceManager>& enemyResources;
    float distanceFromPlayer(float x, float y);
public:
    Map(const sf::Texture &texture, std::vector<ResourceManager> &enemyResources, PlayableCharacter &player,
        std::vector<std::unique_ptr<Enemy>> &enemies);
    void update(const float &dt);
    void render(sf::RenderTarget &target);
    void createMap();
    void placeRooms();
    void createCorridors(const Room &room1, const Room &room2);
    sf::Vector2i getDiredctionToPlayer(float x, float y);
};

#endif //PROGETTO_PROGRAMMAZIONE_MAP_H
