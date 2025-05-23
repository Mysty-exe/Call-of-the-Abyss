#include <Utilities.h>

Texture Utilities::message = Texture();
Vector Utilities::up = Vector(1, -0.5);
Vector Utilities::left = Vector(-1, -0.5);
Vector Utilities::right = Vector(1, 0.5);
Vector Utilities::down = Vector(-1, 0.5);
Vector Utilities::upLeft = Vector(0, -1);
Vector Utilities::downLeft = Vector(-1, 0);
Vector Utilities::downRight = Vector(0, 1);
Vector Utilities::upRight = Vector(1, 0);

Vector Utilities::getIsometricDirection(Vector direction, bool aiming)
{
    Vector newDirection;
    float dotProduct = -1;

    direction = direction.normalize();
    if (direction.magnitude() == 0)
    {
        return Vector(0, 0);
    }

    if (direction.dotProduct(Utilities::up.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::up.normalize());
        newDirection = Utilities::up;
    }
    if (direction.dotProduct(Utilities::upRight.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::upRight.normalize());
        newDirection = Utilities::upRight;
    }
    if (direction.dotProduct(Utilities::upLeft.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::upLeft.normalize());
        newDirection = Utilities::upLeft;
    }
    if (direction.dotProduct(Utilities::down.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::down.normalize());
        newDirection = Utilities::down;
    }
    if (direction.dotProduct(Utilities::downRight.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::downRight.normalize());
        newDirection = Utilities::downRight;
    }
    if (direction.dotProduct(Utilities::downLeft.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::downLeft.normalize());
        newDirection = Utilities::downLeft;
    }
    if (direction.dotProduct(Utilities::left.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::left.normalize());
        newDirection = Utilities::left;
    }
    if (direction.dotProduct(Utilities::right.normalize()) > dotProduct)
    {
        dotProduct = direction.dotProduct(Utilities::right.normalize());
        newDirection = Utilities::right;
    }

    return newDirection.normalize();
}

void Utilities::displayMessage(SDL_Renderer *renderer, float width, float height, string text, int messageLevel, bool bigger)
{
    if (bigger)
    {
        message.loadFromRenderedText(renderer, TTF_OpenFont("Assets/Fonts/font.ttf", 42), text, {88, 38, 148});
    }
    else
    {
        message.loadFromRenderedText(renderer, TTF_OpenFont("Assets/Fonts/font.ttf", 30), text, {255, 255, 255});
    }

    int y = height - ((message.getHeight() + 30) * messageLevel);
    message.setCoords(width / 2 - message.getWidth() / 2, y);
    SDL_Rect rect = {message.getX() - 10, message.getY() - 10, message.getWidth() + 20, message.getHeight() + 20};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(renderer, &rect);
    message.render(renderer, Vector(0, 0));

    message.free();
}
