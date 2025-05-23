#include <Room.h>

class Floor
{
private:
    SDL_Renderer *renderer;
    float width, height;

    int numRooms;
    Room *currentRoom, *nextRoom;
    string nextDoor;
    vector<Room *> rooms;

    Player *player;

    Camera mapCamera;

public:
    Floor();
    Floor(SDL_Renderer *renderer, float width, float height, int numRooms, Player *player);
    static bool sortRooms(Vector vec1, Vector vec2);
    void updateDimensions(float width, float height);
    Room *getRoom();
    Room *getNextRoom();
    void goNextRoom();
    void generateFloor();
    void moveEntities(EventManager *eventManager, MessageManager *msgManager, Camera &camera, double timeStep);
    void displayRoom(EventManager *eventManager, Camera &camera);
    void centerMap();
    void dragMap(Vector offset);
    bool isValidMap();
    void drawMap(int distance);
    void free();
};
