#include <StateManager.h>

StateManager::StateManager(SDL_Renderer *renderer, int width, int height) : Manager(renderer, width, height)
{
    eventManager = new EventManager();
    msgManager = new MessageManager(width, height);
    menuManager = MenuManager(renderer, width, height);
    gameManager = GameManager(renderer, eventManager, msgManager, width, height);

    currentState = GAME;
    cursor.loadFromFile(renderer, "Assets/cursor.png", 1);
    stepTimer.start();
}

ManagerState StateManager::getState()
{
    return currentState;
}

void StateManager::run()
{
    int FPS = 60;
    int FrameStartTimeMs = 0;

    while (currentState != QUIT)
    {
        FrameStartTimeMs = SDL_GetTicks();

        timeStep = stepTimer.getTicks() / 1000.0f;
        timeStep = (timeStep <= 0) ? 0.001 : timeStep;
        timeStep *= 10;
        stepTimer.start();

        eventManager->getEvents();
        currentState = eventManager->userQuit() ? QUIT : currentState;
        updateDimensions(eventManager->getWidth(), eventManager->getHeight());

        switch (currentState)
        {
        case MENU:
            menuManager.run(eventManager, timeStep);
            break;
        case GAME:
            gameManager.run(timeStep);
            break;
        case SETTINGS:
            break;
        }

        msgManager->displayMessages(renderer);
        eventManager->clear();

        cursor.setCoords(eventManager->getMousePos() - Vector(cursor.getWidth() / 2, cursor.getHeight() / 2));
        cursor.render(renderer, Vector(0, 0));

        SDL_RenderPresent(renderer);

        while (SDL_GetTicks() - FrameStartTimeMs < 1000 / FPS)
        {
        }
    }
}

void StateManager::updateDimensions(int w, int h)
{
    if (w != 0 && h != 0)
    {
        width = w;
        height = h;
        menuManager.updateDimensions(w, h);
        gameManager.updateDimensions(w, h);
        msgManager->resizeDimensions(w, h);
    }
}
