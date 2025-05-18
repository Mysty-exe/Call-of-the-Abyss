#include <EventManager.h>

EventManager::EventManager()
{
    quit = false;
    holdingClick = false;
    changedWidth = 0;
    changedHeight = 0;
    leftClick = false;
}

std::vector<KeyEvent> EventManager::getHoldKeyEvents()
{
    return holdKeyEvents;
}

std::vector<KeyEvent> EventManager::getPressKeyEvents()
{
    return pressKeyEvents;
}

bool EventManager::userQuit()
{
    return quit;
}

void EventManager::getEvents()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouseOffset = Vector(x, y) - mousePos;
    mousePos = Vector(x, y);

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                changedWidth = event.window.data1;
                changedHeight = event.window.data2;
            }
        }
        if (event.type == SDL_MOUSEWHEEL)
        {
            mouseWheel.x = event.wheel.x;
            mouseWheel.y = event.wheel.y;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                leftClick = true;
                holdingClick = true;
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                holdingClick = false;
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_SPACE)
            {
                pressKeyEvents.push_back(SPACE);
            }
            if (event.key.keysym.sym == SDLK_UP)
            {
                pressKeyEvents.push_back(UPARROW);
            }
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                pressKeyEvents.push_back(DOWNARROW);
            }
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                pressKeyEvents.push_back(LEFTARROW);
            }
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                pressKeyEvents.push_back(RIGHTARROW);
            }
            if (event.key.keysym.sym == SDLK_m)
            {
                pressKeyEvents.push_back(M);
            }
            if (event.key.keysym.sym == SDLK_e)
            {
                pressKeyEvents.push_back(E);
            }
            if (event.key.keysym.sym == SDLK_r)
            {
                pressKeyEvents.push_back(R);
            }
            if (event.key.keysym.sym == SDLK_t)
            {
                pressKeyEvents.push_back(T);
            }
        }
    }

    keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W])
    {
        holdKeyEvents.push_back(W);
    }
    else if (keys[SDL_SCANCODE_S])
    {
        holdKeyEvents.push_back(S);
    }
    if (keys[SDL_SCANCODE_A])
    {
        holdKeyEvents.push_back(A);
    }
    else if (keys[SDL_SCANCODE_D])
    {
        holdKeyEvents.push_back(D);
    }
}

Vector EventManager::getMouseOffset()
{
    return mouseOffset;
}

Vector EventManager::getMousePos()
{
    return mousePos;
}

SDL_Point EventManager::getPoint()
{
    SDL_Point point = {(int)mousePos.x, (int)mousePos.y};
    return point;
}

SDL_FPoint EventManager::getFPoint()
{
    SDL_FPoint point = {mousePos.x, mousePos.y};
    return point;
}

Vector EventManager::getMouseWheel()
{
    return mouseWheel;
}

bool EventManager::checkHoldKeyEvent(KeyEvent event)
{
    if (std::find(holdKeyEvents.begin(), holdKeyEvents.end(), event) != holdKeyEvents.end())
    {
        return true;
    }
    return false;
}

bool EventManager::checkPressKeyEvent(KeyEvent event)
{
    if (std::find(pressKeyEvents.begin(), pressKeyEvents.end(), event) != pressKeyEvents.end())
    {
        return true;
    }
    return false;
}

bool EventManager::isLeftClick()
{
    return leftClick;
}

bool EventManager::isHoldingClick()
{
    return holdingClick;
}

bool EventManager::changedWindowSize()
{
    return changedWidth != 0 && changedHeight != 0;
}

int EventManager::getWidth()
{
    return changedWidth;
}

int EventManager::getHeight()
{
    return changedHeight;
}

void EventManager::clear()
{
    mouseWheel = Vector(0, 0);
    holdKeyEvents.clear();
    pressKeyEvents.clear();
    changedWidth = 0;
    changedHeight = 0;
    leftClick = false;
}
