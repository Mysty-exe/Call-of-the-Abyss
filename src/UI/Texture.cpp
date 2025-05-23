#include <Texture.h>

Texture::Texture()
{
    texture = NULL;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    rect = {x, y, width, height};
}

Texture::~Texture()
{
}

void Texture::createRenderableTexture(SDL_Renderer *renderer, int width, int height, SDL_TextureAccess access)
{
    free();
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    if (texture != NULL)
    {
        this->width = width;
        this->height = height;
    }
}

void Texture::setAsRenderTarget(SDL_Renderer *renderer)
{
    SDL_SetRenderTarget(renderer, texture);
}

void Texture::loadFromFile(SDL_Renderer *renderer, string path, float multiplier)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    width = loadedSurface->w * multiplier;
    height = loadedSurface->h * multiplier;
    SDL_FreeSurface(loadedSurface);
    rect = {x, y, width, height};
}

void Texture::loadFromFile(SDL_Renderer *renderer, string path, Vector multiplier)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    width = loadedSurface->w * multiplier.x;
    height = loadedSurface->h * multiplier.y;
    SDL_FreeSurface(loadedSurface);
    rect = {x, y, width, height};
}

void Texture::loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, string text, SDL_Color textColor, float multiplier)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    width = textSurface->w * multiplier;
    height = textSurface->h * multiplier;
    SDL_FreeSurface(textSurface);
    rect = {x, y, width, height};
}

void Texture::free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
        rect = {x, y, width, height};
    }
}

void Texture::render(SDL_Renderer *renderer, Vector scroll, float zoom, float angle)
{
    SDL_FPoint point = {0, height / 2};
    SDL_FRect renderQuad = {x - scroll.x, y - scroll.y, width * zoom, height * zoom};
    SDL_RenderCopyExF(renderer, texture, NULL, &renderQuad, angle, &point, SDL_FLIP_NONE);
}

void Texture::setCoords(Vector pos)
{
    this->x = pos.x;
    this->y = pos.y;
    rect = {pos.x, pos.y, width, height};
}

void Texture::setCoords(float x, float y)
{
    this->x = x;
    this->y = y;
    rect = {x, y, width, height};
}

double Texture::getX()
{
    return x;
}

double Texture::getY()
{
    return y;
}

double Texture::getMiddleX()
{
    return x + width / 2;
}

double Texture::getEndX()
{
    return x + width;
}

double Texture::getMiddleY()
{
    return y + height / 2;
}

double Texture::getEndY()
{
    return y + height;
}

float Texture::getWidth()
{
    return width;
}

float Texture::getHeight()
{
    return height;
}

Vector Texture::getSize()
{
    return Vector(width, height);
}

SDL_FRect *Texture::getFRect()
{
    return &rect;
}
