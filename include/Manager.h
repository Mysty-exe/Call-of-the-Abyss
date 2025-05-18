#pragma once
#include "SDL.h"
#include "EventManager.h"

class Manager
{
protected:
    SDL_Renderer *renderer;
    EventManager eventManager;
    int width, height;

public:
    Manager();
    Manager(SDL_Renderer *renderer, int width, int height);
    virtual void updateDimensions(int width, int height) = 0;
};