
#include <Room.h>

Room::Room()
{
}

Room::Room(SDL_Renderer *renderer, float width, float height, Player *player)
{
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    this->player = player;
    discovered = true;
    size = 40;

    northDoor = nullptr;
    southDoor = nullptr;
    eastDoor = nullptr;
    westDoor = nullptr;

    entities.push_back(player);

    portalsActivated = false;
}

int Room::getDoorIndex(string door)
{
    if (door == "North")
    {
        return 0;
    }
    if (door == "South")
    {
        return 1;
    }
    if (door == "East")
    {
        return 2;
    }
    if (door == "West")
    {
        return 3;
    }
}

string Room::getDoorLocation(int num)
{
    if (num == 0)
    {
        return "North";
    }
    if (num == 1)
    {
        return "South";
    }
    if (num == 2)
    {
        return "East";
    }
    if (num == 3)
    {
        return "West";
    }
}

string Room::getOppositeDoor(string door)
{
    if (door == "North")
    {
        return "South";
    }
    if (door == "South")
    {
        return "North";
    }
    if (door == "West")
    {
        return "East";
    }
    if (door == "East")
    {
        return "West";
    }
}

Room *Room::getRoom(string doorType)
{
    if (doorType == "North")
    {
        return northDoor;
    }
    if (doorType == "South")
    {
        return southDoor;
    }
    if (doorType == "East")
    {
        return eastDoor;
    }
    if (doorType == "West")
    {
        return westDoor;
    }
}

bool Room::isDiscovered()
{
    return discovered;
}

void Room::hasDiscovered()
{
    discovered = true;
}

void Room::updateDimensions(float width, float height)
{
    this->width = width;
    this->height = height;
}

bool Room::getPortalsActivated()
{
    return portalsActivated;
}

void Room::addEntity(Entity *entity)
{
    entities.push_back(entity);
}

void Room::addEnemy(Enemy *enemy)
{
    enemies.push_back(enemy);
}

bool Room::isFull()
{
    if (northDoor == nullptr || southDoor == nullptr || eastDoor == nullptr || westDoor == nullptr)
    {
        return false;
    }
    return true;
}

void Room::generateLine(float startX, float startY, float length)
{
    if (length <= 0)
    {
        return;
    }

    Tile tile;
    float y = 0;
    tiles.push_back({});
    for (float x = 0; x < length; x++)
    {
        tile = Tile(renderer, (startX + x * (Tile::getSize() / 2)), (startY + y * (Tile::getSize() / 4)));
        tiles[tiles.size() - 1].push_back(tile);

        y += 1;
    }
}

void Room::generateRoom()
{
    float startX, startY, change, dx, nextDx;
    startX = 0;
    startY = 0;

    for (float y = -size; y < size; y++)
    {
        dx = (float)sqrt(size * size - y * y);
        nextDx = (float)sqrt(size * size - (y + 1) * (y + 1));
        change = (ceil(nextDx - -nextDx) - ceil(dx - -dx)) / 2.0;
        generateLine(startX, startY, ceil(dx - -dx));
        startX -= (Tile::getSize() / 2);
        startY += (Tile::getSize() / 4);
        startX -= (Tile::getSize() / 2) * change;
        startY -= (Tile::getSize() / 4) * change;
    }

    vector<Room *> doors = {northDoor, southDoor, eastDoor, westDoor};
    for (int i = 0; i < doors.size(); i++)
    {
        if (doors[i] == nullptr)
        {
            continue;
        }
        doorLocations.push_back(make_pair(getDoorLocation(i), getDoorTile(getDoorLocation(i)).getPos()));
    }
}

string Room::addRoom(Room *room)
{
    Room *doors[] = {northDoor, southDoor, eastDoor, westDoor};
    vector<int> eligibleDoors = {};
    for (int i = 0; i < 4; i++)
    {
        if (doors[i] == nullptr)
        {
            eligibleDoors.push_back(i);
        }
    }

    int num = rand() % eligibleDoors.size();
    setDoor(eligibleDoors[num], room);

    return getDoorLocation(eligibleDoors[num]);
}

void Room::addRoom(Room *room, string doorLoc)
{
    Room *doors[] = {northDoor, southDoor, eastDoor, westDoor};
    int num = getDoorIndex(getOppositeDoor(doorLoc));
    setDoor(num, room);
}

void Room::removeRoom(Room *room)
{
    if (northDoor == room)
    {
        northDoor = nullptr;
    }
    else if (southDoor == room)
    {
        southDoor = nullptr;
    }
    else if (eastDoor == room)
    {
        eastDoor = nullptr;
    }
    else if (westDoor == room)
    {
        westDoor = nullptr;
    }
}

vector<pair<string, Vector>> Room::getDoorLocations()
{
    return doorLocations;
}

void Room::setDoor(int num, Room *room)
{
    if (num == 0)
    {
        northDoor = room;
    }
    if (num == 1)
    {
        southDoor = room;
    }
    if (num == 2)
    {
        eastDoor = room;
    }
    if (num == 3)
    {
        westDoor = room;
    }
}

void Room::setDoors()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        for (int ii = 0; ii < tiles[i].size(); ii++)
        {
            if (ii == ceil(tiles[i].size() / 2))
            {
                if ((i + 1 == 1 && northDoor != nullptr) || (i + 1 == (size * 2) - 1 && southDoor != nullptr))
                {
                    tiles[i][ii].setPortal();
                }
            }
            else if (i + 1 == size)
            {
                if ((ii == 0 && westDoor != nullptr) || (ii == (size * 2) - 1 && eastDoor != nullptr))
                {
                    tiles[i][ii].setPortal();
                }
            }
        }
    }
}

void Room::togglePortals()
{
    tiles[0][floor((tiles[0].size() - 1) / 2)].toggleActivation();
    tiles[tiles.size() - 1][floor((tiles[0].size() - 1) / 2)].toggleActivation();
    tiles[int((tiles.size() - 1) / 2)][tiles[int((tiles.size() - 1) / 2)].size() - 1].toggleActivation();
    tiles[int((tiles.size() - 1) / 2)][0].toggleActivation();
    portalsActivated = (tiles[0][floor((tiles[0].size() - 1) / 2)].isActivated() || tiles[tiles.size() - 1][floor((tiles[0].size() - 1) / 2)].isActivated() || tiles[int((tiles.size() - 1) / 2)][tiles[int((tiles.size() - 1) / 2)].size() - 1].isActivated() || tiles[int((tiles.size() - 1) / 2)][0].isActivated());
}

Tile Room::getDoorTile(string doorType)
{
    if (doorType == "North")
    {
        return tiles[1][floor((tiles[1].size() - 1) / 2)];
    }
    if (doorType == "South")
    {
        return tiles[tiles.size() - 2][floor((tiles[1].size() - 1) / 2)];
    }
    if (doorType == "East")
    {
        return tiles[int((tiles.size() - 1) / 2)][tiles[int((tiles.size() - 1) / 2)].size() - 2];
    }
    if (doorType == "West")
    {
        return tiles[int((tiles.size() - 1) / 2)][1];
    }
}

Tile Room::getCenter()
{
    return tiles[floor((tiles.size() - 1) / 2)][size];
}

Tile Room::getTile(int row, int col)
{
    if (row >= tiles.size())
    {
        if (col >= tiles[row - 1].size())
        {
            return tiles[row][col];
        }
    }
}

Tile Room::getRandomTile()
{
    int row, col;
    row = rand() % tiles.size();
    col = rand() % tiles[row].size();
    return tiles[row][col];
}

Tile Room::getSpawnableTile()
{
    int x, row, col;
    x = rand() % 2;
    if (x == 0)
    {
        int nums[4] = {0, 1, tiles.size() - 1, tiles.size() - 2};
        row = nums[rand() % 4];
        col = rand() % tiles[row].size();
    }
    else if (x == 1)
    {
        row = rand() % tiles.size();
        int nums[4] = {0, 1, tiles[row].size() - 1, tiles[row].size() - 2};
        col = nums[rand() % 4];
    }

    return tiles[row][col];
}

void Room::addXpParticles(int amount, int xpAmount, Vector pos)
{
    for (int i = 0; i < amount; i++)
    {
        xpParticles.push_back(XP(renderer, pos + Vector(-25 + rand() % 51, -25 + rand() % 51), xpAmount / amount));
    }
}

void Room::moveEntities(EventManager *eventManager, Camera &camera, double timeStep)
{
    player->move(renderer, camera, eventManager, tiles, timeStep);

    for (Enemy *enemy : enemies)
    {
        enemy->trackPlayer(entities, player, camera, tiles, timeStep);
    }

    if (player->isAttacking(eventManager))
    {
        for (Enemy *enemy : enemies)
        {
            if (player->weaponInRange(renderer, enemy->getRect()))
            {
                enemy->dealDamage(player->getDamage());
                if (enemy->getHealth() <= 0)
                {
                    addXpParticles(10, enemy->getXP(), enemy->getPos());
                    enemy->free();
                    delete enemy;
                }
            }
        }
    }

    enemies.erase(
        remove_if(enemies.begin(), enemies.end(),
                  [](Enemy *e)
                  { return e->getHealth() <= 0; }),
        enemies.end());

    entities.erase(
        remove_if(entities.begin(), entities.end(),
                  [](Entity *e)
                  { return e->getHealth() <= 0 && e->getEntityType() != PLAYER; }),
        entities.end());
}

void Room::display(EventManager *eventManager, Camera &camera)
{
    SDL_FPoint point = eventManager->getFPoint();
    for (int i = 0; i < tiles.size(); i++)
    {
        for (Tile &tile : tiles[i])
        {
            tile.display(camera);
        }
    }

    SDL_SetRenderDrawColor(renderer, 88, 38, 148, 255);
    for (XP &xp : xpParticles)
    {
        xp.moveXP(player->getPos());
        xp.drawXP(renderer, camera.getOffset());
        if (xp.isAbsorbed())
        {
            player->addXP(xp.getXP());
        }
    }

    xpParticles.erase(
        remove_if(xpParticles.begin(), xpParticles.end(),
                  [](XP xp)
                  { return xp.isAbsorbed(); }),
        xpParticles.end());

    sort(entities.begin(), entities.end(), Entity::compareY);
    for (Entity *entity : entities)
    {
        bool showHealthbar = false;
        if (SDL_PointInFRect(&point, entity->getRect()) && entity->getEntityType() != PLAYER)
        {
            showHealthbar = true;
        }
        entity->display(renderer, camera, showHealthbar);
    }
}

vector<vector<Tile>> Room::getTiles()
{
    return tiles;
}

void Room::free()
{
    delete player;
    delete northDoor;
    delete southDoor;
    delete eastDoor;
    delete southDoor;

    for (Enemy *enemy : enemies)
    {
        enemy->free();
        delete enemy;
    }

    for (Entity *entity : entities)
    {
        entity->free();
        delete entity;
    }

    for (int i = 0; i < tiles.size(); i++)
    {
        for (Tile &tile : tiles[i])
        {
            tile.free();
        }
    }

    enemies.clear();
    entities.clear();
}
