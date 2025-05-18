#include <GameManager.h>

GameManager::GameManager() : Manager()
{
}

GameManager::GameManager(SDL_Renderer *renderer, EventManager *eventManager, MessageManager *msgManager, int width, int height) : Manager(renderer, width, height)
{
    this->eventManager = eventManager;
    this->msgManager = msgManager;

    state = DUNGEON;
    player = new Player(renderer);
    floor = new Floor(renderer, width, height, 15, player);
    floors.push_back(floor);
    player->setPos(floor->getRoom()->getCenter().getPos());
    camera = Camera(width, height);
    camera.centerOnPosition(player->getPos());
    zoomFactor = 1.2;
    transparency = 0;

    dungeonSurface.createRenderableTexture(renderer, width, height, SDL_TEXTUREACCESS_TARGET);
    mapSurface.createRenderableTexture(renderer, width * 0.75, height * 0.75, SDL_TEXTUREACCESS_TARGET);
    mapSurface.setCoords(width / 2 - mapSurface.getWidth() / 2, -height * 0.75);
    minimapSurface.createRenderableTexture(renderer, width * 0.75, height * 0.75, SDL_TEXTUREACCESS_TARGET);
    // background.loadFromFile(renderer, "Assets/bg.png", 1);

    font = TTF_OpenFont("Assets/Fonts/font.ttf", 24);

    dungeonTimer.start();
}

Vector GameManager::getRenderOffset()
{
    return Vector(((zoomFactor * width - width) / 2), ((zoomFactor * height - height) / 2));
}

void GameManager::drawBackground()
{
    int startX = 0;
    if (-camera.getX() < 0)
    {
        while (true)
        {
            startX -= background.getWidth();
            if (startX < -camera.getX())
            {
                break;
            }
        }
    }

    int startY = 0;
    if (-camera.getY() < 0)
    {
        while (true)
        {
            startY -= background.getHeight();
            if (startY < -camera.getY())
            {
                break;
            }
        }
    }

    for (int i = 0; i <= width; i += background.getWidth())
    {
        for (int ii = 0; ii <= height; ii += background.getHeight())
        {
            // background.setCoords(Vector(i, ii));
            // background.render(renderer, Vector(0, 0));
        }
    }
}

void GameManager::handleZoom()
{
    if (eventManager->getMouseWheel().y > 0)
    {
        zoomFactor += 0.1;
    }
    else if (eventManager->getMouseWheel().y < 0)
    {
        zoomFactor -= 0.1;
    }

    zoomFactor = (zoomFactor > 5) ? 5 : zoomFactor;
    zoomFactor = (zoomFactor < 1) ? 1 : zoomFactor;
}

void GameManager::transition()
{
    SDL_Rect rect = {0, 0, width, height};
    transitioning = true;

    if (floor->getNextRoom() != nullptr)
    {
        msgManager->removeMessage("Press E to Enter Room");

        transparency += 7;
        transparency = (transparency >= 255) ? 255 : transparency;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, transparency);
        SDL_RenderFillRect(renderer, &rect);

        if (transparency >= 255)
        {
            transparency = 255;
            floor->goNextRoom();
            camera.centerOnPosition(player->getPos());
        }
    }
    else if (transparency > 0)
    {
        transparency -= 7;
        transparency = (transparency <= 0) ? 0 : transparency;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, transparency);
        SDL_RenderFillRect(renderer, &rect);
    }
    else
    {
        transitioning = false;
    }
}

void GameManager::processEvents()
{
    if (eventManager->checkPressKeyEvent(M))
    {
        floor->centerMap();
        state = (state == DUNGEON) ? MAP : DUNGEON;
    }
}

void GameManager::renderProfile()
{
    Texture profile, healthbarTxt, healthbarOutline, heartIcon, energyIcon, manaIcon, titleTxt, skillPointsTxt;
    SDL_FRect healthbar;
    float length;

    titleTxt.loadFromRenderedText(renderer, font, player->getTitle() + " - Level " + to_string(player->getLevel()), {255, 255, 255, 255}, 1.5);
    skillPointsTxt.loadFromRenderedText(renderer, font, to_string(player->getSkillPoints()) + " Skill Points Available", {255, 255, 255, 255}, 1.5);

    profile.loadFromFile(renderer, "Assets/UI/Profile/portrait.png", 3);
    profile.setCoords(25, 15);
    profile.render(renderer, Vector(0, 0));

    titleTxt.setCoords(profile.getX() + 15, profile.getY() + profile.getHeight() + 30);
    titleTxt.render(renderer, Vector(0, 0));
    skillPointsTxt.setCoords(titleTxt.getX(), titleTxt.getY() + titleTxt.getHeight() + 10);
    skillPointsTxt.render(renderer, Vector(0, 0));

    heartIcon.loadFromFile(renderer, "Assets/UI/Profile/heartIcon.png", 1.5);
    energyIcon.loadFromFile(renderer, "Assets/UI/Profile/energyIcon.png", 1.5);
    manaIcon.loadFromFile(renderer, "Assets/UI/Profile/manaIcon.png", 1.5);

    SDL_SetRenderDrawColor(renderer, 18, 46, 89, 255);
    length = 300 * (player->getEnergy() / player->getMaxEnergy());
    healthbarTxt.loadFromRenderedText(renderer, font, to_string(player->getEnergy()) + " / " + to_string(player->getMaxEnergy()), {255, 255, 255, 255}, 1);
    healthbarOutline.loadFromFile(renderer, "Assets/UI/Profile/healthbar.png", Vector((305 * (player->getMaxHealth() / 100)) / 150, 40 / 20));
    healthbar = {(float)profile.getEndX() + 15, (float)profile.getMiddleY() - 20, length, 40};
    healthbarOutline.setCoords(healthbar.x - 1, healthbar.y);
    energyIcon.setCoords(healthbarOutline.getMiddleX() - (healthbarTxt.getWidth() + energyIcon.getWidth() + 10) / 2, profile.getMiddleY() - energyIcon.getHeight() / 2);
    healthbarTxt.setCoords(energyIcon.getEndX() + 10, healthbarOutline.getMiddleY() - healthbarTxt.getHeight() / 2);
    SDL_RenderFillRectF(renderer, &healthbar);
    healthbarOutline.render(renderer, Vector(0, 0));
    healthbarTxt.render(renderer, Vector(0, 0));
    energyIcon.render(renderer, Vector(0, 0));

    SDL_SetRenderDrawColor(renderer, 210, 47, 47, 255);
    length = 300 * (player->getHealth() / player->getMaxHealth());
    healthbarTxt.loadFromRenderedText(renderer, font, to_string((int)player->getHealth()) + " / " + to_string((int)player->getMaxHealth()), {255, 255, 255, 255}, 1);
    healthbarOutline.loadFromFile(renderer, "Assets/UI/Profile/healthbar.png", Vector((305 * (player->getMaxHealth() / 100)) / 150, 40 / 20));
    healthbar = {(float)profile.getEndX() - 5, (float)(profile.getY() + profile.getHeight() * 0.25 - 25), length, 40};
    healthbarOutline.setCoords(healthbar.x - 1, healthbar.y);
    heartIcon.setCoords(healthbarOutline.getMiddleX() - (healthbarTxt.getWidth() + heartIcon.getWidth() + 10) / 2, profile.getY() + profile.getHeight() * 0.25 - heartIcon.getHeight() / 2 - 5);
    healthbarTxt.setCoords(heartIcon.getEndX() + 10, healthbarOutline.getMiddleY() - healthbarTxt.getHeight() / 2);
    SDL_RenderFillRectF(renderer, &healthbar);
    healthbarOutline.render(renderer, Vector(0, 0));
    healthbarTxt.render(renderer, Vector(0, 0));
    heartIcon.render(renderer, Vector(0, 0));

    SDL_SetRenderDrawColor(renderer, 68, 33, 95, 255);
    length = 300 * (player->getMana() / player->getMaxMana());
    healthbarTxt.loadFromRenderedText(renderer, font, to_string(player->getMana()) + " / " + to_string(player->getMaxMana()), {255, 255, 255, 255}, 1);
    healthbarOutline.loadFromFile(renderer, "Assets/UI/Profile/healthbar.png", Vector((305 * (player->getMaxMana() / 100)) / 150, 40 / 20));
    healthbar = {(float)profile.getEndX() - 5, (float)(profile.getY() + profile.getHeight() * 0.75 - 15), length, 40};
    healthbarOutline.setCoords(healthbar.x - 1, healthbar.y);
    manaIcon.setCoords(healthbarOutline.getMiddleX() - (healthbarTxt.getWidth() + manaIcon.getWidth() + 10) / 2, profile.getY() + profile.getHeight() * 0.75 - manaIcon.getHeight() / 2 + 5);
    healthbarTxt.setCoords(manaIcon.getEndX() + 10, healthbarOutline.getMiddleY() - healthbarTxt.getHeight() / 2);
    SDL_RenderFillRectF(renderer, &healthbar);
    healthbarOutline.render(renderer, Vector(0, 0));
    healthbarTxt.render(renderer, Vector(0, 0));
    manaIcon.render(renderer, Vector(0, 0));
}
void GameManager::runUI()
{
    Texture floorTxt, border;

    renderProfile();

    border.loadFromFile(renderer, "Assets/UI/Border/squareBorder.png", Vector(350.0 / 100.0, 350.0 / 100.0));

    if (state != MAP)
    {
        floor->centerMap();
    }

    float time = dungeonTimer.getTicks();
    string mins = to_string((int)std::floor(time / 60000.0));
    time = fmod(time, 60000);
    string secs = to_string((int)std::floor(time / 1000.0));
    mins = (mins.length() == 1) ? "0" + mins : mins;
    secs = (secs.length() == 1) ? "0" + secs : secs;

    string text = "floor " + to_string(floors.size()) + " - " + mins + ":" + secs;
    floorTxt.loadFromRenderedText(renderer, font, text, {255, 255, 255, 255}, 3);
    floorTxt.setCoords(width / 2 - floorTxt.getWidth() / 2, 25);
    floorTxt.render(renderer, Vector(0, 0));

    if (state == MAP)
    {
        return;
    }

    SDL_Point point = eventManager->getPoint();
    SDL_Rect mapRect = {width - 355, 5, 350, 350};
    if (SDL_PointInRect(&point, &mapRect) && eventManager->isLeftClick())
    {
        state = MAP;
        return;
    }

    SDL_Rect rect = {minimapSurface.getWidth() / 2 - (330.0 / 2), minimapSurface.getHeight() / 2 - (330.0 / 2), 330, 330};
    minimapSurface.setAsRenderTarget(renderer);
    SDL_RenderSetClipRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderFillRect(renderer, &rect);
    floor->drawMap(100);

    SDL_SetRenderTarget(renderer, NULL);

    border.setCoords(width - 355, 5);
    minimapSurface.setCoords(width - 180, 180);
    minimapSurface.render(renderer, minimapSurface.getSize() / 2);
    border.render(renderer, Vector(0, 0));
}

void GameManager::runMap()
{
    if (eventManager->isHoldingClick())
    {
        floor->dragMap(eventManager->getMouseOffset());
    }

    floor->drawMap(250);
}

void GameManager::run(double timeStep)
{
    processEvents();

    Vector cameraOffset = (player->getPos() - camera.getCenter()) / 40.0;
    cameraOffset = (cameraOffset.magnitude() < 0.01) ? Vector(0, 0) : cameraOffset;
    camera.centerOnPosition(camera.getCenter() + cameraOffset);
    camera.shakeScreen();

    // drawBackground();

    dungeonSurface.setAsRenderTarget(renderer);
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    if (state != MAP || mapSurface.getY() <= -height * 0.75)
    {
        if (eventManager->checkPressKeyEvent(R))
        {
            Enemy *e = new Enemy(renderer);
            e->setPos(floor->getRoom()->getSpawnableTile().getPos());
            floor->getRoom()->addEntity(e);
            floor->getRoom()->addEnemy(e);
        }
        if (eventManager->checkPressKeyEvent(T))
        {
            floor->getRoom()->togglePortals();
        }

        handleZoom();
        player->processEvents(eventManager);
        floor->moveEntities(eventManager, msgManager, camera, timeStep);
    }

    floor->displayRoom(eventManager, camera);

    SDL_SetRenderTarget(renderer, NULL);
    dungeonSurface.setCoords(0 - getRenderOffset().x, 0 - getRenderOffset().y);
    dungeonSurface.render(renderer, Vector(0, 0), zoomFactor);

    runUI();
    transition();

    if (state == MAP || mapSurface.getY() > -height * 0.75)
    {
        Texture border;
        SDL_Rect rect = {20, 20, width * 0.75 - 40, height * 0.75 - 40};
        mapSurface.setAsRenderTarget(renderer);
        SDL_RenderSetClipRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderFillRect(renderer, &rect);

        runMap();
        SDL_SetRenderTarget(renderer, NULL);

        if (state != MAP)
        {
            float y = (mapSurface.getY() - 75 < -height * 0.75) ? -height * 0.75 : mapSurface.getY() - 75;
            mapSurface.setCoords(width / 2 - mapSurface.getWidth() / 2, y);
        }
        else if (mapSurface.getY() < height / 2 - mapSurface.getHeight() / 2)
        {
            float y = (mapSurface.getY() + 75 > height / 2 - mapSurface.getHeight() / 2) ? height / 2 - mapSurface.getHeight() / 2 : mapSurface.getY() + 75;
            mapSurface.setCoords(width / 2 - mapSurface.getWidth() / 2, y);
        }
        else
        {
            mapSurface.setCoords(width / 2 - mapSurface.getWidth() / 2, height / 2 - mapSurface.getHeight() / 2);
        }

        mapSurface.render(renderer, Vector(0, 0), 1);

        border.loadFromFile(renderer, "Assets/UI/Border/wideBorder.png", Vector((width * 0.75 + 10) / 320, (height * 0.75 + 10) / 180));
        border.setCoords(width / 2 - border.getWidth() / 2, mapSurface.getY());
        border.render(renderer, Vector(0, 0));
    }
}

void GameManager::updateDimensions(int width, int height)
{
    this->width = width;
    this->height = height;
    camera.updateDimensions(width, height);
    floor->updateDimensions(width, height);
    floor->centerMap();

    dungeonSurface.createRenderableTexture(renderer, width, height, SDL_TEXTUREACCESS_TARGET);
    mapSurface.createRenderableTexture(renderer, width * 0.75, height * 0.75, SDL_TEXTUREACCESS_TARGET);
    minimapSurface.createRenderableTexture(renderer, width * 0.75, height * 0.75, SDL_TEXTUREACCESS_TARGET);
}
