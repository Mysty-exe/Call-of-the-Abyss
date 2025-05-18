#include <Tile.h>

Tile::Tile()
{
}

Tile::Tile(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    tile.loadFromFile(renderer, "Assets/Tiles/tile.png", 2);
    deactivatedPortal.loadFromFile(renderer, "Assets/Tiles/Portal/Deactivated/portal.png", 2);

    width = tile.getWidth();
    height = tile.getHeight();
    position = Vector(tile.getX(), tile.getY());
    isPortal = false;
    activated = false;
}

Tile::Tile(SDL_Renderer *renderer, double x, double y)
{
    this->renderer = renderer;
    tile.loadFromFile(renderer, "Assets/Tiles/tile.png", 2);
    deactivatedPortal.loadFromFile(renderer, "Assets/Tiles/Portal/Deactivated/portal.png", 2);

    tile.setCoords(x, y);
    deactivatedPortal.setCoords(x, y);
    activatedPortal.setCoords(x, y);

    width = tile.getWidth();
    height = tile.getHeight();
    position = Vector(x, y);
    isPortal = false;
    activated = false;
}

float Tile::getSize()
{
    return 64;
}

void Tile::setPortal()
{
    isPortal = true;
    if (activatedPortal.getImages().size() == 0)
    {
        activatedPortal.loadAnimation(renderer, "Assets/Tiles/Portal/Activated", 2, 0.1);
    }
}

void Tile::toggleActivation()
{
    if (isPortal)
    {
        activated = !activated;
        (activated) ? activatedPortal.startAnimation() : activatedPortal.stopAnimation();
    }
}

bool Tile::isActivated()
{
    return activated;
}

void Tile::setCoords(double x, double y)
{
    position = Vector(x, y);
    tile.setCoords(x, y);
    deactivatedPortal.setCoords(x, y);
    activatedPortal.setCoords(x, y);
}

int Tile::getWidth()
{
    return width;
}

int Tile::getHeight()
{
    return height;
}

Vector Tile::getOriginalPos()
{
    return Vector(position.x, position.y);
}

Vector Tile::getPos()
{
    return Vector(position.x + width / 2, position.y + height / 4);
}

void Tile::display(Camera camera)
{
    if (!isPortal)
    {
        tile.render(renderer, camera.getOffset());
    }
    else
    {
        if (activated)
        {
            activatedPortal.render(renderer, camera.getOffset());
        }
        else
        {
            deactivatedPortal.render(renderer, camera.getOffset());
        }
    }
}

bool Tile::pointInTile(Vector P)
{
    Vector A = position + Vector(0, height / 4);
    Vector B = position + Vector(width / 2, height / 2);
    Vector C = position + Vector(width, height / 4);
    Vector D = position + Vector(width / 2, 0);

    Vector Q = (A + C) * 0.5;
    float a = 0.5 * A.distance(C);
    float b = 0.5 * B.distance(D);
    Vector U = (C - A) / (2 * a);
    Vector V = (D - B) / (2 * b);

    Vector W = P - Q;
    float xabs = abs(W.dotProduct(U));
    float yabs = abs(W.dotProduct(V));

    return xabs / a + yabs / b <= 1.00;
}
