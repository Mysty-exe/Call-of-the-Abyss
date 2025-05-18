#pragma once
#include "SDL.h"
#include <Vector.h>
#include <Texture.h>
#include <Animation.h>
#include "Camera.h"

class Tile
{
private:
    SDL_Renderer *renderer;
    Vector position;
    int width, height;
    Texture tile, deactivatedPortal;
    Animation activatedPortal;
    bool isPortal, activated;

public:
    Tile();
    Tile(SDL_Renderer *renderer);
    Tile(SDL_Renderer *renderer, double x, double y);
    static float getSize();
    void setPortal();
    void toggleActivation();
    bool isActivated();
    void setCoords(double x, double y);
    int getWidth();
    int getHeight();
    Vector getOriginalPos();
    Vector getPos();
    void display(Camera camera);
    bool pointInTile(Vector P);
};
