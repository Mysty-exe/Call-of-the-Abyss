#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <Vector.h>

using namespace std;

class Texture
{
public:
    Texture();
    ~Texture();
    void createRenderableTexture(SDL_Renderer *renderer, int width, int height, SDL_TextureAccess access);
    void setAsRenderTarget(SDL_Renderer *renderer);
    void loadFromFile(SDL_Renderer *renderer, string path, float multiplier = 1);
    void loadFromFile(SDL_Renderer *renderer, string path, Vector multiplier = Vector(1, 1));
    void loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, string textureText, SDL_Color textColor, float multiplier = 1);
    void free();
    void render(SDL_Renderer *renderer, Vector scroll, float zoom = 1, float angle = 0);
    void setCoords(Vector pos);
    void setCoords(float x, float y);
    double getX();
    double getY();
    double getMiddleX();
    double getEndX();
    double getMiddleY();
    double getEndY();
    float getWidth();
    float getHeight();
    Vector getSize();
    SDL_FRect *getFRect();

private:
    float x, y;
    float width, height;
    SDL_Texture *texture;
    SDL_FRect rect;
};