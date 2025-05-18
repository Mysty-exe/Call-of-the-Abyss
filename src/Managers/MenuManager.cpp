#include <MenuManager.h>

MenuManager::MenuManager() : Manager()
{
}

MenuManager::MenuManager(SDL_Renderer *renderer, int width, int height) : Manager(renderer, width, height)
{
}

void MenuManager::run(EventManager *eventManager, double timeStep)
{
}

void MenuManager::updateDimensions(int width, int height)
{
    this->width = width;
    this->height = height;
}
