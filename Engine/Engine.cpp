#include <chrono>
#include <iostream>
#include <SDL.h>
#include <string>
#include <vector>

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
    for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i)
    {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i,&info);
        std::cout << i << ": " << info.name << "\n";
    }
    SDL_GetNumRenderDrivers();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

    //SDL_SetRelativeMouseMode(SDL_TRUE);

    std::vector<Vector2> freestylepoints;
    std::vector<Vector2> linepoints;
    Uint32 lineengage = 0;
    
    auto startnano = std::chrono::high_resolution_clock::now();
    
    while (true)
    {
        SDL_PumpEvents();
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        // draw and update

        //update
        Vector2 tempvector(0,0);
        Uint32 buttons = SDL_GetMouseState(&tempvector.x,&tempvector.y);
        if (buttons == 1)
        {
            freestylepoints.push_back(tempvector);
        }
        else if (buttons == 2 && lineengage != 2)
        {
            linepoints.push_back(tempvector);
            std::cout << tempvector.x << ", " << tempvector.y << "\n";
        }
        lineengage = buttons;

        //draw
        for (int i = 0; i < freestylepoints.size(); ++i)
        {
            SDL_SetRenderDrawColor(renderer, rand()%255, rand()%255, rand()%255, 255);
            SDL_RenderDrawPoint(renderer,freestylepoints.at(i).x,freestylepoints.at(i).y);
        }
        if (linepoints.size() > 1)
        {
            for (int i = 0; i < linepoints.size()-1; ++i)
            {
                SDL_SetRenderDrawColor(renderer, rand()%255, rand()%255, rand()%255, 255);
                SDL_RenderDrawLine(renderer,linepoints.at(i).x,linepoints.at(i).y,linepoints.at(i+1).x,linepoints.at(i+1).y);
            }
        }

        //render at my computer's refresh rate, 60hz
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {
            startnano = nextnano;

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}
