#include <iostream>
#include "SDL.h"
#include "StateManager.h"
#include "filesystem"

const std::string TITLE = "Call of the Abyss";
const int WIDTH = 1280 * 2;
const int HEIGHT = 720 * 2;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowMinimumSize(window, 900, 600);
    SDL_ShowCursor(SDL_DISABLE);

    std::filesystem::current_path(filesystem::path(argv[0]).parent_path());

    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);
    TTF_Init();

    SDL_Surface *icon = IMG_Load("Assets/Icons/gameIcon.png");
    SDL_SetWindowIcon(window, icon);

    StateManager stateManager = StateManager(renderer, WIDTH, HEIGHT);
    stateManager.run();
    stateManager.free();

    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();

    return 0;
}
