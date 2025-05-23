#pragma once
#include <iostream>
#include "SDL.h"
#include <Vector.h>
#include <vector>
#include "algorithm"

enum KeyEvent
{
    RIGHTCLICK,
    LEFTCLICK,
    HOLDINGCLICK,
    W,
    A,
    S,
    D,
    UPARROW,
    DOWNARROW,
    RIGHTARROW,
    LEFTARROW,
    SPACE,
    ENTER,
    M,
    R,
    T,
    E
};

class EventManager
{
private:
    SDL_Event event;
    std::vector<KeyEvent> holdKeyEvents, pressKeyEvents;
    bool leftClick, holdingClick, quit;
    Vector mousePos, mouseOffset, mouseWheel;
    const Uint8 *keys;

    int changedWidth, changedHeight;

public:
    EventManager();
    bool userQuit();
    void getEvents();
    std::vector<KeyEvent> getHoldKeyEvents();
    std::vector<KeyEvent> getPressKeyEvents();
    Vector getMouseOffset();
    Vector getMousePos();
    Vector getMouseWheel();
    SDL_Point getPoint();
    SDL_FPoint getFPoint();
    bool checkHoldKeyEvent(KeyEvent event);
    bool checkPressKeyEvent(KeyEvent event);
    bool isLeftClick();
    bool isHoldingClick();
    bool changedWindowSize();
    int getWidth();
    int getHeight();
    void clear();
    void free();
};
