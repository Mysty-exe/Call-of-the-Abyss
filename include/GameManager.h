#pragma once
#include <SDL.h>
#include <iostream>
#include <Manager.h>
#include <EventManager.h>
#include <MessageManager.h>
#include <Floor.h>
#include <Room.h>
#include <Player.h>
#include <Enemy.h>
#include <Vector.h>
#include <vector>
#include <Timer.h>
#include "Camera.h"

enum GameState
{
    MAP,
    DUNGEON
};

class GameManager : public Manager
{
private:
    EventManager *eventManager;
    MessageManager *msgManager;

    GameState state;
    vector<Floor *> floors;
    Floor *floor;
    Player *player;
    Camera camera;
    Timer dungeonTimer;
    float zoomFactor, transparency;
    bool transitioning;

    Texture dungeonSurface, mapSurface, minimapSurface, background;
    TTF_Font *font;

public:
    GameManager();
    GameManager(SDL_Renderer *renderer, EventManager *eventManager, MessageManager *msgManager, int width, int height);
    void drawBackground();
    Vector getRenderOffset();
    void handleZoom();
    void transition();
    void processEvents();
    void renderProfile();
    void runUI();
    void runMap();
    void run(double timeStep);
    void updateDimensions(int width, int height);
};