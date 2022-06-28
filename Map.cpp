//
// Created by luca on 24/06/22.
//

#include <SFML/Graphics/Texture.hpp>
#include "Map.h"

Map::Map(const sf::Texture &texture, ResourceManager &enemyResources, PlayableCharacter &player,
         std::vector<std::unique_ptr<Enemy>> &enemies) : player(player), enemies(enemies), texture(texture),
                                                         tileHeight(32), tileWidth(32), sizeX(600), sizeY(200), roomQuantity(20), enemyResources(enemyResources){
    //TODO maybe use enum for tiles
    tiles["VOID"]=sf::IntRect (0*tileWidth,0*tileHeight,tileWidth,tileHeight);
    tiles["GRASS"]=sf::IntRect (0*tileWidth,15*tileHeight,tileWidth,tileHeight);
    tiles["TERRAIN"]=sf::IntRect (0*tileWidth,14*tileHeight,tileWidth,tileHeight);
    tiles["WALL"]=sf::IntRect (4*tileWidth,16*tileHeight,tileWidth,tileHeight);
    createMap();
}

void Map::update(const float &dt) {
    sf::IntRect wall=tiles.at("WALL");
    sf::Vector2f pos,size;
    Hitbox hitbox=player.getHitbox();
    pos=hitbox.getPosition();
    pos.x/=tileWidth;
    pos.y/=tileHeight;
    size=hitbox.getSize();
    size.x/=tileWidth;
    size.y/=tileHeight;

     for(float i=0;i<size.x+1;i++)
         for(float j=0;j<size.y+1;j++) {
             if (i > size.x)
                 i = size.x;
             if(j>size.y)
                 j=size.y;
             if (map[pos.x + i][pos.y + j].tile.getTextureRect() == wall)
                 player.undoMove();
         }
    pos=player.getPosition();
    pos.x/=tileWidth;
    pos.y/=tileHeight;
    Enemy::updateTimer(dt);
    //FIXME fix enemies stuck on corners
    if(Enemy::canChangeDirection()){
        pos.y+=0.5;
        map[pos.x][pos.y].distance=0;
        map[pos.x+1][pos.y].distance=1;
        map[pos.x][pos.y+1].distance=1;
        map[pos.x-1][pos.y].distance=1;
        map[pos.x][pos.y-1].distance=1;
        for(int i=0;i<25;i++)
            for(int j=0;j<25;j++) {
                if(map[pos.x+i][pos.y+j].tile.getTextureRect()==wall)
                    map[pos.x+i][pos.y+j].distance=-1;
                else
                    if(i!=0||j!=0)
                        map[pos.x+i][pos.y+j].distance= distanceFromPlayer(pos.x+i,pos.y+j);

            }
        for(int i=0;i>-25;i--)
            for(int j=0;j<25;j++) {
                if(map[pos.x+i][pos.y+j].tile.getTextureRect()==wall)
                    map[pos.x+i][pos.y+j].distance=-1;
                else
                if(i!=0||j!=0)
                    map[pos.x+i][pos.y+j].distance= distanceFromPlayer(pos.x+i,pos.y+j);

            }
        for(int i=0;i<25;i++)
            for(int j=0;j>-25;j--) {
                if(map[pos.x+i][pos.y+j].tile.getTextureRect()==wall)
                    map[pos.x+i][pos.y+j].distance=-1;
                else
                if(i!=0||j!=0)
                    map[pos.x+i][pos.y+j].distance= distanceFromPlayer(pos.x+i,pos.y+j);

            }
        for(int i=0;i>-25;i--)
            for(int j=0;j>-25;j--) {
                if(map[pos.x+i][pos.y+j].tile.getTextureRect()==wall)
                    map[pos.x+i][pos.y+j].distance=-1;
                else
                if(i!=0||j!=0)
                    map[pos.x+i][pos.y+j].distance= distanceFromPlayer(pos.x+i,pos.y+j);

            }
    }
    for(auto & enemy : enemies){
         hitbox=enemy->getHitbox();
         pos=hitbox.getPosition();
         pos.x/=tileWidth;
         pos.y/=tileHeight;
         size=hitbox.getSize();
         size.x/=tileWidth;
         size.y/=tileHeight;
         for(float i=0;i<size.x+1;i++)
             for(float j=0;j<size.y+1;j++) {
                 if (i > size.x)
                     i = size.x;
                 if(j>size.y)
                     j=size.y;
                 if (map[pos.x + i][pos.y + j].tile.getTextureRect() == wall)
                     enemy->undoMove();
         }
        if(enemy->isAggroed()&&Enemy::canChangeDirection())
            enemy->setDirection(getDiredctionToPlayer(pos.x,pos.y));
    }
    Enemy::resetTimer();
}

void Map::render(sf::RenderTarget &target) {
    sf::View view=target.getView();
    int limitLeft=view.getCenter().x-view.getSize().x/2;
    int limitTop=view.getCenter().y-view.getSize().y/2;
    int limitRight=view.getCenter().x+view.getSize().x/2;
    int limitBottom=view.getCenter().y+view.getSize().y/2;
    if(limitLeft<0) {
        limitLeft = 0;
        view.setCenter(view.getSize().x / 2, view.getCenter().y);
    }
    else if(limitRight>sizeX*tileWidth)
    {
        limitRight=sizeX*tileWidth;
        view.setCenter(sizeX*tileWidth-view.getSize().x / 2, view.getCenter().y);
    }
    if(limitTop<0) {
        limitTop = 0;
        view.setCenter(view.getCenter().x, view.getSize().y / 2);
    }
    else if(limitBottom>sizeY*tileHeight)
    {
        limitBottom=sizeY*tileHeight;
        view.setCenter(view.getCenter().x, sizeY*tileHeight-view.getSize().y / 2);
    }
    target.setView(view);
    limitLeft/=tileWidth;
    limitRight/=tileWidth;
    limitTop/=tileHeight;
    limitBottom/=tileHeight;
#if DEBUG
    sf::Font font;
    font.loadFromFile("../Config/ComicSans.ttf");
    sf::Text distance;
    distance.setFont(font);
    distance.setCharacterSize(10);
#endif
    for(int i=limitLeft-1;i<limitRight+1;i++)
        for(int j=limitTop-1;j<limitBottom+1;j++)
            if(i>=0&&i<sizeX&&j>=0&&j<sizeY) {
                target.draw(map[i][j].tile);
#if DEBUG
                distance.setString(std::to_string(map[i][j].distance));
                distance.setPosition(i*tileWidth,j*tileHeight);
                target.draw(distance);
#endif
            }
}

void Map::createMap() {
    for(int i=0;i<sizeX;++i) {
        map.emplace_back();
        for (int j = 0; j < sizeY; ++j) {
            map[i].push_back(Tile(sf::RectangleShape(sf::Vector2f(tileWidth, tileHeight))));
            map[i][j].tile.setTexture(&texture);
            map[i][j].tile.setTextureRect(tiles.at("GRASS"));
            map[i][j].tile.setPosition(i * tileWidth, j * tileHeight);
        }
    }
    placeRooms();
}
void Map::placeRooms() {
    srand((unsigned int)time(nullptr));
    int roomMinSize=12;
    int roomRandSize=10;
    int horizontalBorder=50;
    int verticalBorder=50;
    for(int i=0,maxLoops=0;i<roomQuantity&&maxLoops<1000;++i,++maxLoops){
        int x=rand()%(sizeX - (roomMinSize+roomRandSize) - horizontalBorder) + horizontalBorder;
        int y=rand()%(sizeY-(roomMinSize+roomRandSize)-verticalBorder)+verticalBorder;
        int w=roomMinSize+rand()%(roomRandSize+1);
        int h=roomMinSize+rand()%(roomRandSize+1);
        Room room(w,h,x,y);
        bool intersects=false;
        if(rooms.empty()) {
            player.setPosition((x+5)*tileWidth,(y+5)*tileHeight);
        }
        for(int j=0;j<rooms.size()&&!intersects;++j)
            if(room.intersects(rooms.at(j)))
                intersects=true;
        if(!intersects) {
            for (int j = x; j < x + w; j++)
                for (int k = y; k < y + h; k++)
                    if(j==x||k==y||j==x+w-1||k==y+h-1) {
                        if (map[j][k].tile.getTextureRect() != tiles.at("TERRAIN"))
                            map[j][k].tile.setTextureRect(tiles.at("WALL"));
                    }
                    else {
                        map[j][k].tile.setTextureRect(tiles.at("TERRAIN"));
                        //FIXME enemies spawn inside walls
                        if(rand()%200==1)
                            enemies.emplace_back(std::make_unique<Enemy>(
                                    enemyResources, j * tileWidth, k * tileHeight, rand() % 2));
                    }
            for(auto & j : rooms)
                createCorridors(room,j);
            rooms.push_back(room);
        }
        else
            i--;
    }
}

void Map::createCorridors(const Room &room1, const Room &room2) {
    if(abs(room1.getCenter().x-room2.getCenter().x)>100)
        return;
    int startX,startY,endX,endY;
    if(room1.getCenter().x>room2.getCenter().x) {
        startX = room2.getCenter().x;
        endX = room1.getCenter().x;
        startY=room2.getCenter().y;
        endY=room1.getCenter().y;
    }
    else
    {
        startX = room1.getCenter().x;
        endX = room2.getCenter().x;
        startY=room1.getCenter().y;
        endY=room2.getCenter().y;
    }
    for(int i=startX; i < endX; i++){
        if(map[i][startY - 2].tile.getTextureRect() != tiles.at("TERRAIN"))
            map[i][startY - 2].tile.setTextureRect(tiles.at("WALL"));
        map[i][startY - 1].tile.setTextureRect(tiles.at("TERRAIN"));
        if(rand()%20==1)
            enemies.emplace_back(std::make_unique<Enemy>(
                    enemyResources, i * tileWidth, startY * tileHeight, rand() % 2));
        map[i][startY].tile.setTextureRect(tiles.at("TERRAIN"));
        map[i][startY + 1].tile.setTextureRect(tiles.at("TERRAIN"));
        if(map[i][startY + 2].tile.getTextureRect() != tiles.at("TERRAIN"))
            map[i][startY + 2].tile.setTextureRect(tiles.at("WALL"));
    }
    bool isStartYBigger= startY>endY;
    if(map[endX+1][startY+1-2*!isStartYBigger].tile.getTextureRect()!=tiles.at("TERRAIN"))
        map[endX+1][startY+1-2*!isStartYBigger].tile.setTextureRect(tiles.at("WALL"));
    if(map[endX][startY+1-2*!isStartYBigger].tile.getTextureRect()!=tiles.at("TERRAIN"))
        map[endX][startY+1-2*!isStartYBigger].tile.setTextureRect(tiles.at("WALL"));
    for(int i=startY; i != endY; i+=(1-2*isStartYBigger)){
        if(map[endX - 2][i].tile.getTextureRect() != tiles.at("TERRAIN"))
            map[endX - 2][i].tile.setTextureRect(tiles.at("WALL"));
        map[endX - 1][i].tile.setTextureRect(tiles.at("TERRAIN"));
        if(rand()%20==1)
            enemies.emplace_back(std::make_unique<Enemy>(
                    enemyResources, endX * tileWidth, i * tileHeight, rand() % 2));
        map[endX][i].tile.setTextureRect(tiles.at("TERRAIN"));
        map[endX + 1][i].tile.setTextureRect(tiles.at("TERRAIN"));
        if(map[endX + 2][i].tile.getTextureRect() != tiles.at("TERRAIN"))
            map[endX + 2][i].tile.setTextureRect(tiles.at("WALL"));
    }
}

float Map::distanceFromPlayer(float x, float y) {
    float sum=0;
    float min=800;
    for(int i=-1;i<2;i++)
        for(int j=-1;j<2;j++)
            if(map[x+i][y+j].distance>=0&&map[x+i][y+j].distance<min&&(i!=0||j!=0)) {
                min = map[x + i][y + j].distance;
                if(abs(i)+abs(j)==1)
                    sum=1;
                else
                    sum=1.44;
            }
    return min+sum;
}

sf::Vector2i Map::getDiredctionToPlayer(float x, float y) {
    sf::Vector2i direction;
    float min=800;
    for(int i=-1;i<2;i++)
        for(int j=-1;j<2;j++)
            if(map[x+i][y+j].distance>=0&&map[x+i][y+j].distance<min&&(i!=0||j!=0)) {
                min = map[x + i][y + j].distance;
                direction=sf::Vector2i (i,j);
            }
    return direction;
}

Map::Room::Room(int width, int height, int x, int y):
        topLeftCoordinates(x,y), width(width),height(height){}

sf::Vector2i Map::Room::getCenter() const {
    return {topLeftCoordinates.x+width/2,topLeftCoordinates.y+height/2};
}

bool Map::Room::intersects(const Room &otherRoom) const {
    int minDistance =4;
    return (topLeftCoordinates.x-minDistance<=otherRoom.topLeftCoordinates.x+otherRoom.width&&
            topLeftCoordinates.x+width+minDistance>=otherRoom.topLeftCoordinates.x&&
            topLeftCoordinates.y-minDistance<=otherRoom.topLeftCoordinates.y+otherRoom.height&&
            topLeftCoordinates.y+height+minDistance>=otherRoom.topLeftCoordinates.y);
}