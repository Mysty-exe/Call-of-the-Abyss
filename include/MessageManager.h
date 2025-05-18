#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <Timer.h>
#include <Utilities.h>
#include <algorithm>
#include <string>

using namespace std;

class MessageManager
{
private:
    float width, height;
    vector<pair<int, string>> messages;
    vector<Timer *> messageTimers;

public:
    MessageManager();
    MessageManager(float width, float height);
    void resizeDimensions(float width, float height);
    void addMessage(string msg, int type);
    void removeMessage(string msg);
    void displayMessages(SDL_Renderer *renderer);
};