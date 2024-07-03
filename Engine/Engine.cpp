#include <chrono>
#include <iostream>
#include <SDL.h>
#include <string>

#include "Vector2.h"

int main(int argc, char* argv[])
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // create window
    // returns pointer to window if successful or nullptr if failed
    SDL_Window* window = SDL_CreateWindow("Game Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    Vector2 mousepos(0,0);
    
    auto startnano = std::chrono::high_resolution_clock::now();
    
    while (true)
    {
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        auto nextnano = std::chrono::high_resolution_clock::now();
        // draw and update
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {
            startnano = nextnano;

            //update
            SDL_GetMouseState(&mousepos.x,&mousepos.y);

            //draw
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            std::cout << mousepos.x << ", " << mousepos.y << "\n";
            //SDL_RenderDrawPoint(renderer,mousepos.x,mousepos.y);
        }
        
        // show screen
        SDL_RenderPresent(renderer);
    }

    return 0;
}
