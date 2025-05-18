#include <Animation.h>

Animation::Animation()
{
}

void Animation::loadAnimation(SDL_Renderer *renderer, string folder, float multiplier, double frameSecs)
{
    this->frameSecs = frameSecs;
    this->folder = folder;
    currentFrame = 0;
    images = {};
    loadFrames(renderer, multiplier);
}

void Animation::loadFrames(SDL_Renderer *renderer, float multiplier)
{
    images.clear();
    int size = -1;
    for (auto &f : filesystem::directory_iterator(folder))
    {
        size++;
    }

    for (int x = 1; x <= size; x++)
    {
        Texture image;
        image.loadFromFile(renderer, folder + "/" + to_string(x) + ".png", multiplier);
        images.push_back(image);
    }
}

void Animation::setCoords(float x, float y)
{
    pos = Vector(x, y);
}

void Animation::freeAll()
{
    for (Texture image : images)
    {
        image.free();
    }
    images = {};
}

void Animation::startAnimation()
{
    frameTimer.start();
}

void Animation::stopAnimation()
{
    frameTimer.reset();
}

void Animation::render(SDL_Renderer *renderer, Vector offset)
{
    images[currentFrame].setCoords(pos.x, pos.y);
    images[currentFrame].render(renderer, offset);

    if (frameTimer.getTicks() / 1000 >= frameSecs)
    {
        currentFrame += 1;
        if (currentFrame >= images.size())
        {
            currentFrame = 0;
        }
        frameTimer.start();
    }
}

Vector Animation::getPos()
{
    return pos;
}

float Animation::getWidth()
{
    return images[0].getWidth();
}

float Animation::getHeight()
{
    return images[0].getHeight();
}

Vector Animation::getSize()
{
    return images[0].getSize();
}

vector<Texture> Animation::getImages()
{
    return images;
}

int Animation::getCurrentFrame()
{
    return currentFrame;
}
