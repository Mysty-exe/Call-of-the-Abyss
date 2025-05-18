#pragma once
#include <SDL.h>
#include <iostream>
#include <Manager.h>
#include <EventManager.h>

class MenuManager : public Manager
{
public:
    MenuManager();
    MenuManager(SDL_Renderer *renderer, int width, int height);
    void run(EventManager *eventManager, double timeStep);
    void updateDimensions(int width, int height);
};