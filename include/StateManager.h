#pragma once
#include <SDL.h>
#include <iostream>
#include <Manager.h>
#include <EventManager.h>
#include <MessageManager.h>
#include <MenuManager.h>
#include <GameManager.h>
#include <Camera.h>
#include <Timer.h>

enum ManagerState
{
    MENU,
    GAME,
    SETTINGS,
    QUIT
};

class StateManager : public Manager
{
private:
    MenuManager menuManager;
    GameManager gameManager;
    EventManager *eventManager;
    MessageManager *msgManager;
    ManagerState currentState;
    Timer stepTimer;
    double timeStep;

    Texture cursor;

public:
    StateManager(SDL_Renderer *renderer, int width, int height);
    ManagerState getState();
    void run();
    void updateDimensions(int width, int height);
};