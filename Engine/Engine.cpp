#include <chrono>
#include <iostream>
#include <SDL.h>
#include <fmod.hpp>
#include <string>
#include <vector>

#include "Vector2.h"
#include "Particle.h"

int win_h = 600;
int win_w = 800;

/*
void fireworks(SDL_Renderer* renderer)
{
    std::vector<Vector2> freestylepoints;
    std::vector<Vector2> linepoints;
    std::vector<Particle> particles;
    Uint32 lineengage = 0;
    
    auto startnano = std::chrono::high_resolution_clock::now();
    
    while (true)
    {
        SDL_PumpEvents();
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        // draw and update
        /*
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

        Vector2 tempvector(0,0);
        Uint32 buttons = SDL_GetMouseState(&tempvector.x,&tempvector.y);
        if (buttons == 1 && lineengage != 1)
        {
            for (int i = 0; i < 3; ++i)
            {
                int u = 3+(rand()%5);
                float v = (6+(rand()%30))/6;
                int r = std::max(64 + (rand()%255),255);
                int g = std::max(64 + (rand()%255),255);
                int b = std::max(64 + (rand()%255),255);
                for (int i = 0; i < u; ++i)
                {
                    float steprads = (i * (360/u)) * (3.14f / 180);
                    Particle firework = Particle(FVector2(tempvector.x,tempvector.y),FVector2(cos(steprads) * v,sin(steprads) * v));
                    particles.push_back(Particle(firework.pos,firework.velocity,r,g,b));
                }
            }
        }
        lineengage = buttons;
        
        //render at my computer's refresh rate, 60hz
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {
            startnano = nextnano;

            for (int i = 0; i < particles.size(); ++i)
            {
                if (particles.at(i).Update() && particles.size() > 0)
                {
                    //particles.erase(std::next(particles.begin(),i));
                }
                particles.at(i).Draw(renderer);
            }

            SDL_RenderPresent(renderer);
        }
    }

}
*/

void drumMachine(SDL_Renderer* renderer, FMOD::System* audio)
{
    FMOD::Sound* sound = nullptr;
    int cha, rcha;
    const Uint8* keystate;
    bool lastkey[] = {0,0,0,0,0,0};
    
    std::vector<FMOD::Sound*> sounds;
    audio->createSound("snd/tr808/bass.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("snd/tr808/clap.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("snd/tr808/close-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("snd/tr808/cowbell.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("snd/tr808/open-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("snd/tr808/snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    
    auto startnano = std::chrono::high_resolution_clock::now();

    
    
    while(true)
    {
        SDL_PumpEvents();
        audio->getChannelsPlaying(&cha,&rcha);
        keystate = SDL_GetKeyboardState(nullptr);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        if (keystate[SDL_SCANCODE_Q])
        {
            if (!lastkey[0])
            {
                audio->playSound(sounds[0],nullptr,false,nullptr);
            }
            lastkey[0] = 1;
        }
        else { lastkey[0] = 0; }
        
        if (keystate[SDL_SCANCODE_W])
        {
            if (!lastkey[1])
            {
                audio->playSound(sounds[5],nullptr,false,nullptr);
            }
            lastkey[1] = 1;
        }
        else { lastkey[1] = 0; }

        if (keystate[SDL_SCANCODE_E])
        {
            if (!lastkey[2])
            {
                audio->playSound(sounds[2],nullptr,false,nullptr);
            }
            lastkey[2] = 1;
        }
        else { lastkey[2] = 0; }

        if (keystate[SDL_SCANCODE_R])
        {
            if (!lastkey[3])
            {
                audio->playSound(sounds[1],nullptr,false,nullptr);
            }
            lastkey[3] = 1;
        }
        else { lastkey[3] = 0; }
        
        if (keystate[SDL_SCANCODE_T])
        {
            if (!lastkey[4])
            {
                audio->playSound(sounds[3],nullptr,false,nullptr);
            }
            lastkey[4] = 1;
        }
        else { lastkey[4] = 0; }

        if (keystate[SDL_SCANCODE_Y])
        {
            if (!lastkey[5])
            {
                audio->playSound(sounds[4],nullptr,false,nullptr);
            }
            lastkey[5] = 1;
        }
        else { lastkey[5] = 0; }
        
        //render at my computer's refresh rate, 60hz
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        
        if (nanointerval > (1000000000/60))
        {
            startnano = nextnano;
            for (int i = 0; i < 6; ++i)
            {
                if (lastkey[i])
                {
                    float xcoord = static_cast<float>(win_w) * (((float)i+1)/7);
                    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
                    SDL_RenderDrawPoint(renderer,static_cast<int>(xcoord),win_h/2);
                }
            }
            SDL_RenderPresent(renderer);
        }
        
        audio->update();
    }
}

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
        win_w, win_h,
        SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // create renderer
    /*
    for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i)
    {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i,&info);
        std::cout << i << ": " << info.name << "\n";
    }
    */
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

    //SDL_SetRelativeMouseMode(SDL_TRUE);

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    drumMachine(renderer, audio);
    
    return 0;
}
