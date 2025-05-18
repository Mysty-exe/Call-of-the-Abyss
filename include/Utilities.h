#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <Texture.h>
#include <Vector.h>

class Utilities
{
public:
    static Texture message;
    static Vector up, down, left, right, upRight, upLeft, downRight, downLeft;
    static Vector getIsometricDirection(Vector direction, bool aiming = false);
    static void displayMessage(SDL_Renderer *renderer, float width, float height, string text, int messageLevel = 1);
};