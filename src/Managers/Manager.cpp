#include <Manager.h>

Manager::Manager()
{
}

Manager::Manager(SDL_Renderer *renderer, int width, int height)
{
    this->renderer = renderer;
    this->eventManager = eventManager;
    this->width = width;
    this->height = height;
}