#include <Entity.h>

Entity::Entity()
{
    width = 24;
    height = 24;
    position = Vector(50, 50);
    gravity = Vector(0, 0);
    rect = {50, 50, width, height};
    currentRow = -1;
    currentCol = -1;
    velocity = 0;
    level = 1;
}

string Entity::getTitle()
{
    return title;
}

int Entity::getLevel()
{
    return level;
}

bool Entity::compareY(Entity *e1, Entity *e2)
{
    return (e1->getPos().y < e2->getPos().y);
}

EntityType Entity::getEntityType()
{
    return entityType;
}

Vector Entity::getPos()
{
    return position + Vector(width / 2, height / 2);
}

void Entity::setPos(Vector pos)
{
    prevPosition = position;
    position = pos - Vector(width / 2, height);
    currentRow = -1;
    currentCol = -1;
}

int Entity::getCurrentRow()
{
    return currentRow;
}

int Entity::getCurrentCol()
{
    return currentCol;
}

Vector Entity::getDirection()
{
    return direction;
}

int Entity::getWidth()
{
    return width;
}

int Entity::getHeight()
{
    return height;
}

SDL_FRect *Entity::getRect()
{
    return &rect;
}

float Entity::getHealth()
{
    return health;
}

float Entity::getMaxHealth()
{
    return maxHealth;
}

void Entity::setEntityDirection()
{
    if (entity.size() < 2)
    {
        return;
    }

    if (Utilities::getIsometricDirection(aimDirection) == Utilities::up.normalize())
    {
        currentEntity = entity[0];
    }
    else if (Utilities::getIsometricDirection(aimDirection) == Utilities::down.normalize())
    {
        currentEntity = entity[1];
    }
    else if (Utilities::getIsometricDirection(aimDirection) == Utilities::left.normalize())
    {
        currentEntity = entity[2];
    }
    else if (Utilities::getIsometricDirection(aimDirection) == Utilities::right.normalize())
    {
        currentEntity = entity[3];
    }
    else if (Utilities::getIsometricDirection(aimDirection) == Utilities::upLeft.normalize())
    {
        currentEntity = entity[4];
    }
    else if (Utilities::getIsometricDirection(aimDirection) == Utilities::upRight.normalize())
    {
        currentEntity = entity[5];
    }
    else if (Utilities::getIsometricDirection(aimDirection) == Utilities::downLeft.normalize())
    {
        currentEntity = entity[6];
    }
    else if (Utilities::getIsometricDirection(aimDirection) == Utilities::downRight.normalize())
    {
        currentEntity = entity[7];
    }
}

void Entity::display(SDL_Renderer *renderer, Camera camera, bool showHealthbar)
{
    int drawX = static_cast<int>(round(position.x));
    int drawY = static_cast<int>(round(position.y));
    currentEntity->setCoords((int)drawX, (int)drawY);
    currentEntity->render(renderer, camera.getOffset());

    Vector pos = position - Vector(0, height / 5 + 10) - camera.getOffset();
    if (showHealthbar)
    {
        healthBar.displayHealthbar(pos, Vector(width, height / 5));
    }

    if (entityType == PLAYER)
    {
        weapon.setRange(getPos() - camera.getOffset(), aimDirection);
        // weapon.displayArea(renderer);
    }
    else
    {
        healthBar.displayDmgNumbers(camera.getOffset());
    }
}

void Entity::move(vector<vector<Tile>> tiles, double timeStep)
{
}

void Entity::checkEdge(vector<vector<Tile>> tiles, double timeStep)
{
    bool footOnPlatform1, footOnPlatform2;
    footOnPlatform1 = false;
    footOnPlatform2 = false;

    int startRow, endRow;
    startRow = (currentRow != -1) ? currentRow - 3 : 0;
    endRow = (currentRow != -1) ? currentRow + 3 : tiles.size();
    startRow = (startRow < 0) ? 0 : startRow;
    endRow = (endRow > tiles.size()) ? tiles.size() : endRow;

    for (int i = startRow; i < endRow; i++)
    {
        for (int ii = 0; ii < tiles[i].size(); ii++)
        {
            Tile tile = tiles[i][ii];
            if (tile.pointInTile(position + Vector(0, height - 2)))
            {
                currentRow = i;
                currentCol = ii;
                footOnPlatform1 = true;
            }
            if (tile.pointInTile(position + Vector(width, height - 2)))
            {
                currentRow = i;
                currentCol = ii;
                footOnPlatform2 = true;
            }
        }
    }

    if (!footOnPlatform1 || !footOnPlatform2)
    {
        position = prevPosition;
        velocity = 0;
    }
}

void Entity::dealDamage(float damage)
{
    healthBar.dealDamage(position + Vector(rand() % int(width), 0), damage);
    health = healthBar.getHealth();
}

void Entity::free()
{
    for (Animation *e : entity)
    {
        e->freeAll();
    }

    currentEntity->freeAll();
    healthBar.free();
}
