#pragma once
#include <iostream>
#include <SDL.h>
#include <Texture.h>
#include <Vector.h>
#include <vector>
#include <Timer.h>
#include <filesystem>

class Animation
{
private:
    string folder;
    std::vector<Texture> images;
    double currentFrame, frameSecs;
    Timer frameTimer;
    Vector pos;

public:
    Animation();
    Animation(SDL_Renderer *renderer, string folder, float multiplier, double frameSecs);
    void loadAnimation(SDL_Renderer *renderer, string folder, float multiplier, double frameSecs);
    void loadFrames(SDL_Renderer *renderer, float multiplier);
    void startAnimation();
    void stopAnimation();
    void render(SDL_Renderer *renderer, Vector offset);
    void setCoords(float x, float y);
    void freeAll();
    Vector getPos();
    float getWidth();
    float getHeight();
    Vector getSize();
    vector<Texture> getImages();
    int getCurrentFrame();
};
