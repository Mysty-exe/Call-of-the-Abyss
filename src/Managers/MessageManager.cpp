#include <MessageManager.h>

MessageManager::MessageManager()
{
}

MessageManager::MessageManager(float width, float height)
{
    resizeDimensions(width, height);
}

void MessageManager::resizeDimensions(float width, float height)
{
    this->width = width;
    this->height = height;
}

void MessageManager::addMessage(string msg, int type)
{
    if (messages.size() >= 1)
    {
        messages.erase(messages.begin());
    }

    messages.push_back(make_pair(type, msg));
}

void MessageManager::removeMessage(string msg)
{
    for (int i = messages.size() - 1; i > -1; i--)
    {
        if (messages[i].second == msg)
        {
            messages.erase(messages.begin() + i);
        }
    }
}

void MessageManager::displayMessages(SDL_Renderer *renderer)
{
    for (int i = 0; i < messages.size(); i++)
    {
        Utilities::displayMessage(renderer, width, height, messages[i].second, i + 1);
    }
}
