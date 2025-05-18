#pragma once
#include <algorithm>
#include "SDL.h"
#include "Tile.h"
#include "Vector.h"
#include "vector"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "MessageManager.h"
#include "Camera.h"
#include "Texture.h"

using namespace std;

class Room
{
private:
    SDL_Renderer *renderer;
    float width, height, size;

    Room *northDoor, *southDoor, *eastDoor, *westDoor;
    vector<pair<string, Vector>> doorLocations;
    vector<vector<Tile>> tiles;
    vector<Entity *> entities;
    vector<Enemy *> enemies;
    Player *player;
    bool discovered;

    bool portalsActivated;

public:
    Room();
    Room(SDL_Renderer *renderer, float width, float height, Player *player);
    static int getDoorIndex(string door);
    static string getDoorLocation(int num);
    static string getOppositeDoor(string door);
    bool isDiscovered();
    void hasDiscovered();
    Room *getRoom(string doorType);
    void updateDimensions(float width, float height);
    bool getPortalsActivated();
    void addEntity(Entity *entity);
    void addEnemy(Enemy *enemy);
    bool isFull();
    void generateLine(float startX, float startY, float length);
    void generateRoom();
    string addRoom(Room *room);
    void addRoom(Room *room, string doorLoc);
    void removeRoom(Room *room);
    vector<pair<string, Vector>> getDoorLocations();
    void setDoor(int num, Room *room);
    void setDoors();
    void togglePortals();
    Tile getDoorTile(string doorType);
    Tile getCenter();
    Tile getTile(int row, int col);
    Tile getRandomTile();
    Tile getSpawnableTile();
    void moveEntities(EventManager *eventManager, Camera &camera, double timeStep);
    void display(EventManager *eventManager, Camera &camera);
    vector<vector<Tile>> getTiles();
};
