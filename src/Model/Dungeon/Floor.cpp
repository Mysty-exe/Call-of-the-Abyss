#include <Floor.h>

Floor::Floor()
{
}

Floor::Floor(SDL_Renderer *renderer, float width, float height, int numRooms, Player *player)
{
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    this->numRooms = numRooms;
    this->player = player;
    mapCamera = Camera(width * 0.75, height * 0.75);

    currentRoom = new Room(renderer, width, height, this->player);
    currentRoom->hasDiscovered();
    nextRoom = nullptr;

    rooms.push_back(currentRoom);
    generateFloor();
}

void Floor::updateDimensions(float width, float height)
{
    mapCamera = Camera(width * 0.75, height * 0.75);
    for (Room *room : rooms)
    {
        room->updateDimensions(width, height);
    }
}

Room *Floor::getRoom()
{
    return currentRoom;
}

Room *Floor::getNextRoom()
{
    return nextRoom;
}

void Floor::goNextRoom()
{
    currentRoom = nextRoom;
    currentRoom->hasDiscovered();
    player->setPos(currentRoom->getDoorTile(currentRoom->getOppositeDoor(nextDoor)).getPos());
    nextRoom = nullptr;
}

void Floor::generateFloor()
{
    for (int i = 1; i < numRooms; i++)
    {
        vector<Room *> eligibleRooms = {};
        for (Room *room : rooms)
        {
            if (!room->isFull())
            {
                eligibleRooms.push_back(room);
            }
        }

        if (eligibleRooms.size() == 0)
        {
            continue;
        }

        Room *room = new Room(renderer, width, height, player);
        Room *randomRoom = eligibleRooms[rand() % eligibleRooms.size()];
        string doorLoc = randomRoom->addRoom(room);
        room->addRoom(randomRoom, doorLoc);
        rooms.push_back(room);

        if (!isValidMap())
        {
            randomRoom->removeRoom(room);
            rooms.pop_back();
            i--;
        }
    }

    for (Room *room : rooms)
    {
        room->generateRoom();
        room->setDoors();
    }
}

void Floor::moveEntities(EventManager *eventManager, MessageManager *msgManager, Camera &camera, double timeStep)
{
    player->update(eventManager, msgManager);
    currentRoom->moveEntities(eventManager, camera, timeStep);

    bool closeToDoor = false;
    for (pair<string, Vector> door : currentRoom->getDoorLocations())
    {
        if (player->getPos().distance(door.second) < 100 && currentRoom->getPortalsActivated())
        {
            closeToDoor = true;
            msgManager->addMessage("Press E to Enter Room", 0);
            if (eventManager->checkPressKeyEvent(E))
            {
                if (currentRoom->getRoom(door.first) != nullptr)
                {
                    nextRoom = currentRoom->getRoom(door.first);
                    nextDoor = door.first;
                    break;
                }
            }
        }
    }

    if (!closeToDoor)
    {
        msgManager->removeMessage("Press E to Enter Room");
    }
}

void Floor::displayRoom(EventManager *eventManager, Camera &camera)
{
    currentRoom->display(eventManager, camera);
}

void Floor::centerMap()
{
    mapCamera.centerOnPosition(Vector(0, 0));
}

void Floor::dragMap(Vector offset)
{
    mapCamera.drag(offset);
}

bool Floor::isValidMap()
{
    SDL_Rect rect;
    Vector currentPos;

    bool done = false;
    Room *current = rooms[0];
    vector<Room *> visited;
    vector<Vector> visitedPos;
    vector<pair<Room *, Vector>> last;
    visited.push_back(current);
    visitedPos.push_back(currentPos);
    last.push_back(make_pair(current, currentPos));

    while (!done)
    {
        float num = 200;
        if (current->getRoom("North") != nullptr && find(visited.begin(), visited.end(), current->getRoom("North")) == visited.end())
        {
            if (current->getRoom("North")->isDiscovered())
            {
                currentPos -= Vector(0, 200);
                Vector drawPos = currentPos - mapCamera.getOffset();

                current = current->getRoom("North");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);
                visitedPos.push_back(currentPos);

                continue;
            }
        }

        if (current->getRoom("South") != nullptr && find(visited.begin(), visited.end(), current->getRoom("South")) == visited.end())
        {
            if (current->getRoom("South")->isDiscovered())
            {
                currentPos += Vector(0, 200);

                current = current->getRoom("South");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);
                visitedPos.push_back(currentPos);

                continue;
            }
        }

        if (current->getRoom("East") != nullptr && find(visited.begin(), visited.end(), current->getRoom("East")) == visited.end())
        {
            if (current->getRoom("East")->isDiscovered())
            {
                currentPos += Vector(200, 0);

                current = current->getRoom("East");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);
                visitedPos.push_back(currentPos);

                continue;
            }
        }

        if (current->getRoom("West") != nullptr && find(visited.begin(), visited.end(), current->getRoom("West")) == visited.end())
        {
            if (current->getRoom("West")->isDiscovered())
            {
                currentPos -= Vector(200, 0);
                Vector drawPos = currentPos - mapCamera.getOffset();

                current = current->getRoom("West");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);
                visitedPos.push_back(currentPos);

                continue;
            }
        }

        last.pop_back();
        if (last.size() == 0)
        {
            done = true;
            break;
        }

        current = last[last.size() - 1].first;
        currentPos = last[last.size() - 1].second;
    }

    for (Vector v1 : visitedPos)
    {
        int once = 0;
        for (Vector v2 : visitedPos)
        {
            if (v1 == v2)
            {
                once += 1;
            }
            if (once > 1)
            {
                return false;
            }
        }
    }

    return true;
}

void Floor::drawMap(int distance)
{
    Texture roomTexture;
    Vector currentPos;

    bool done = false;
    Room *current = currentRoom;
    vector<Room *> visited;
    vector<Vector> visitedPos;
    vector<pair<Room *, Vector>> last;
    visited.push_back(current);
    visitedPos.push_back(currentPos);
    last.push_back(make_pair(current, currentPos));

    roomTexture.loadFromFile(renderer, "Assets/Map/room.png", 1);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    while (!done)
    {
        float num = distance;
        if (current->getRoom("North") != nullptr && find(visited.begin(), visited.end(), current->getRoom("North")) == visited.end())
        {
            if (current->getRoom("North")->isDiscovered())
            {
                currentPos -= Vector(0, num);
                Vector drawPos = currentPos - mapCamera.getOffset();

                SDL_RenderDrawLine(renderer, drawPos.x, drawPos.y + num, drawPos.x, drawPos.y);
                SDL_RenderDrawLine(renderer, drawPos.x - 1, drawPos.y + num, drawPos.x - 1, drawPos.y);
                SDL_RenderDrawLine(renderer, drawPos.x + 1, drawPos.y + num, drawPos.x + 1, drawPos.y);

                current = current->getRoom("North");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);

                roomTexture.setCoords(drawPos.x - roomTexture.getWidth() / 2, drawPos.y - roomTexture.getHeight() / 2);
                roomTexture.render(renderer, Vector(0, 0));

                continue;
            }
        }

        if (current->getRoom("South") != nullptr && find(visited.begin(), visited.end(), current->getRoom("South")) == visited.end())
        {
            if (current->getRoom("South")->isDiscovered())
            {
                currentPos += Vector(0, num);
                Vector drawPos = currentPos - mapCamera.getOffset();

                SDL_RenderDrawLine(renderer, drawPos.x, drawPos.y - num, drawPos.x, drawPos.y);
                SDL_RenderDrawLine(renderer, drawPos.x - 1, drawPos.y - num, drawPos.x - 1, drawPos.y);
                SDL_RenderDrawLine(renderer, drawPos.x + 1, drawPos.y - num, drawPos.x + 1, drawPos.y);

                current = current->getRoom("South");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);

                roomTexture.setCoords(drawPos.x - roomTexture.getWidth() / 2, drawPos.y - roomTexture.getHeight() / 2);
                roomTexture.render(renderer, Vector(0, 0));

                continue;
            }
        }

        if (current->getRoom("East") != nullptr && find(visited.begin(), visited.end(), current->getRoom("East")) == visited.end())
        {
            if (current->getRoom("East")->isDiscovered())
            {
                currentPos += Vector(num, 0);
                Vector drawPos = currentPos - mapCamera.getOffset();

                SDL_RenderDrawLine(renderer, drawPos.x - num, drawPos.y, drawPos.x, drawPos.y);
                SDL_RenderDrawLine(renderer, drawPos.x - num, drawPos.y - 1, drawPos.x, drawPos.y - 1);
                SDL_RenderDrawLine(renderer, drawPos.x - num, drawPos.y + 1, drawPos.x, drawPos.y + 1);

                current = current->getRoom("East");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);

                roomTexture.setCoords(drawPos.x - roomTexture.getWidth() / 2, drawPos.y - roomTexture.getHeight() / 2);
                roomTexture.render(renderer, Vector(0, 0));

                continue;
            }
        }

        if (current->getRoom("West") != nullptr && find(visited.begin(), visited.end(), current->getRoom("West")) == visited.end())
        {
            if (current->getRoom("West")->isDiscovered())
            {
                currentPos -= Vector(num, 0);
                Vector drawPos = currentPos - mapCamera.getOffset();

                SDL_RenderDrawLine(renderer, drawPos.x + num, drawPos.y, drawPos.x, drawPos.y);
                SDL_RenderDrawLine(renderer, drawPos.x + num, drawPos.y - 1, drawPos.x, drawPos.y - 1);
                SDL_RenderDrawLine(renderer, drawPos.x + num, drawPos.y + 1, drawPos.x, drawPos.y + 1);

                current = current->getRoom("West");
                last.push_back(make_pair(current, currentPos));
                visited.push_back(current);

                roomTexture.setCoords(drawPos.x - roomTexture.getWidth() / 2, drawPos.y - roomTexture.getHeight() / 2);
                roomTexture.render(renderer, Vector(0, 0));

                continue;
            }
        }

        last.pop_back();
        if (last.size() == 0)
        {
            done = true;
            break;
        }

        current = last[last.size() - 1].first;
        currentPos = last[last.size() - 1].second;
    }

    roomTexture.loadFromFile(renderer, "Assets/Map/currentRoom.png", 1);
    roomTexture.setCoords(-roomTexture.getWidth() / 2, -roomTexture.getHeight() / 2);
    roomTexture.render(renderer, mapCamera.getOffset());
}

void Floor::free()
{
    currentRoom->free();
    for (Room *room : rooms)
    {
        room->free();
        delete room;
    }

    rooms.clear();

    delete currentRoom;
}
