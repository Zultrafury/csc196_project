#include <chrono>
#include <iostream>
#include <SDL.h>
#include <fmod.hpp>
#include <SDL_ttf.h>
#include <string>
#include <vector>

#include "Enemy.h"
#include "Font.h"
#include "Vector2.h"
#include "Particle.h"
#include "Model.h"
#include "Star.h"
#include "Text.h"

const int win_h = 900;
const int win_w = 1200;

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

/* void drumMachine(SDL_Renderer* renderer, FMOD::System* audio)
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
} */

/*
void spiral(SDL_Renderer* renderer)
{
    std::vector<FVector2> linepoints;
    linepoints.push_back(FVector2(0,0));
    linepoints.push_back(FVector2(-1,1));
    linepoints.push_back(FVector2(0,2));
    linepoints.push_back(FVector2(1,0));
    linepoints.push_back(FVector2(0,-2));
    linepoints.push_back(FVector2(-2,-1));
    linepoints.push_back(FVector2(-3,1));
    linepoints.push_back(FVector2(-2,3));
    linepoints.push_back(FVector2(0,4));
    linepoints.push_back(FVector2(2,3));
    linepoints.push_back(FVector2(3,0));
    linepoints.push_back(FVector2(0,-4));
    linepoints.push_back(FVector2(-4,-2));
    linepoints.push_back(FVector2(-5,1));
    linepoints.push_back(FVector2(-4,4));
    linepoints.push_back(FVector2(-1,5));

    for (int i = 0; i < linepoints.size(); ++i)
    {
        linepoints[i].x *= 40;
        linepoints[i].y *= 40;
    }
    
    Model model = Model(FVector2(win_w/2,win_h/2),linepoints);
    
    auto startnano = std::chrono::high_resolution_clock::now();
    
    while (true)
    {
        SDL_PumpEvents();
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Vector2 tempvector(0,0);
        Uint32 buttons = SDL_GetMouseState(&tempvector.x,&tempvector.y);
        
        
        //render at my computer's refresh rate, 60hz
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {
            startnano = nextnano;

            model.Draw(renderer);

            SDL_RenderPresent(renderer);
        }
    }

}
*/

/*
void fonttext(SDL_Renderer* renderer)
{
    // load font
    Font* font = new Font();
    font->Load("Jupiteroid-Regular.ttf", 40);

    Text* text = new Text(font);
    text->Create(renderer, "Hello World", SDL_Color{255, 255, 255, 255});

    auto startnano = std::chrono::high_resolution_clock::now();

    while (true)
    {
        SDL_PumpEvents();
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //render at my computer's refresh rate, 60hz
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano - startnano).count();
        if (nanointerval > (1000000000 / 60))
        {
            startnano = nextnano;

            text->Draw(renderer, win_w/2 - 60, win_h/2 - 20);

            SDL_RenderPresent(renderer);
        }
    }
}
*/

void runGame(SDL_Renderer* renderer, FMOD::System* audio)
{
    int ticks = 0; int beats = 0;
    FMOD::Sound* sound = nullptr;
    int cha, rcha;
    const Uint8* keystate;
    bool lastkey[] = {0,0,0,0,0,0};

    //Player
    int lives = 3; int invuln = 0;
    std::vector<FVector2> playermodel;
    playermodel.emplace_back(1,0); playermodel.emplace_back(0.75,0.75); playermodel.emplace_back(0,1);
    playermodel.emplace_back(-0.75,0.75); playermodel.emplace_back(-1,0); playermodel.emplace_back(-0.75,-0.75);
    playermodel.emplace_back(0,-1); playermodel.emplace_back(0.75,-0.75); playermodel.emplace_back(1,0);
    for (int i = 0; i < playermodel.size(); ++i)
    {
        playermodel[i].x *= 20;
        playermodel[i].y *= 20;
    }
    Model player = Model(FVector2(win_w/2,win_h/2),playermodel);

    //Music
    std::vector<FMOD::Sound*> sounds;
    FMOD::ChannelGroup* musicgroup = nullptr;
    audio->createChannelGroup("Music",&musicgroup);
    audio->createSound("snd/music.wav", FMOD_LOOP_NORMAL, 0, &sound);
    sounds.push_back(sound);
    audio->playSound(sounds[0],musicgroup,false,nullptr);
    float musvolume = 0.8f;
    musicgroup->setVolume(musvolume);

    //Sounds
    audio->createSound("snd/hurt.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    //Stars
    std::vector<Star> stars;

    //Enemies
    std::vector<Enemy> enemies;

    //Score + lives
    int score = 0;
    Font* font = new Font();
    font->Load("Jupiteroid-Regular.ttf", 40);
    Text* scoretext = new Text(font);
    Text* livestext = new Text(font);
    Uint8 playerpulse = 0;
    
    auto startnano = std::chrono::high_resolution_clock::now();
    auto bstartnano = std::chrono::high_resolution_clock::now();
    bool onbeat = false;
    int beattype = 1;
    float pulse = 0; 
    
    while(true)
    {
        SDL_PumpEvents();
        audio->getChannelsPlaying(&cha,&rcha);
        keystate = SDL_GetKeyboardState(nullptr);
        
        if (keystate[SDL_SCANCODE_MINUS])
        {
            musvolume = std::fmaxf(musvolume - 0.00001f,0.0);
            musicgroup->setVolume(musvolume);
        }

        if (keystate[SDL_SCANCODE_EQUALS])
        {
            musvolume = std::fminf(musvolume + 0.00001f,1.0);
            musicgroup->setVolume(musvolume);
        }

        //Move player to mouse
        int mousex = 0; int mousey = 0;
        SDL_GetMouseState(&mousex,&mousey);
        if (lives > 0)
        {
            player.center = FVector2(mousex+5, mousey+9);
            if (lives == 1)
            {
                player.center.x += (rand()%3) - 1;
                player.center.y += (rand()%3) - 1;
            }
        }
        
        //render at my computer's refresh rate, 60hz
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();

        //Accurate bpm timing
        auto bnextnano = std::chrono::high_resolution_clock::now();
        auto bnanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(bnextnano-bstartnano).count();

        if (bnanointerval > static_cast<int>(21.68674699*(1000000000.0/60)))
        {
            bstartnano = bnextnano;
            onbeat = true;
            beattype++;
        }
        
        if (nanointerval > (1000000000/60))
        {
            ticks++;
            startnano = nextnano;
            
            if (lives > 0)
            {
                //Board
                if (onbeat)
                {
                    if (lives > 0) { score += 25; }
                    if (beattype%2 == 1)
                    {
                        pulse = 88;
                    }
                    else
                    {
                        pulse = 64;
                    }
                }
                if (beattype%2 == 1)
                {
                    pulse = std::fmaxf(pulse-3,0);
                }
                else
                {
                    pulse = std::fmaxf(pulse-1.5,0);
                }
                Uint8 pulse8 = static_cast<Uint8>(std::trunc(pulse));
                SDL_SetRenderDrawColor(renderer, pulse8, 0, 0, 255);
                SDL_RenderClear(renderer);

                //Stars
                //Star generation
                if (ticks % 5 == 0)
                {
                    stars.emplace_back(FVector2(rand()%win_w,0),FVector2(0,8));
                }
            
                //Star update + draw
                SDL_SetRenderDrawColor(renderer,255,255,255,192);
                for (int i = 0; i < stars.size(); ++i)
                {
                    stars[i].Update();
                    if (stars[i].pos.y > win_h)
                    {
                        std::swap(stars[i],stars.back());
                        stars.pop_back();
                    }
                    stars[i].Draw(renderer);
                }

                //Enemies
                //Enemy generation
                if ((onbeat && beattype%2 == 1) || (onbeat && score > 2000))
                {
                    enemies.emplace_back(win_w,win_h,playermodel);
                }
            
                //Enemy update + draw
                SDL_SetRenderDrawColor(renderer,255,0,0,255);
                for (int i = 0; i < enemies.size(); ++i)
                {
                    if (enemies[i].Update(&player, ticks))
                    {
                        std::swap(enemies[i],enemies.back());
                        enemies.pop_back();
                    }

                    //When within hit distance of player
                    float hitrange = FVector2(enemies[i].center.x-player.center.x,enemies[i].center.y-player.center.y).Magnitude();
                    if (hitrange < 10 && invuln < 1)
                    {
                        audio->playSound(sounds[1],nullptr,false,nullptr);
                        lives--;
                        invuln = 60;
                    }
                    enemies[i].Draw(renderer);
                }
            
            
                //Player drawing
                playerpulse = 255 - (static_cast<Uint8>(std::trunc(pulse)) * ((3/std::max(lives,1))-1));
                SDL_SetRenderDrawColor(renderer, playerpulse, playerpulse-(invuln*3), playerpulse-(invuln*3), playerpulse);
                player.Draw(renderer);
                invuln = std::max(invuln-1,0);

                //Text drawing
                scoretext->Create(renderer, std::to_string(score), SDL_Color{255, 255, 255, playerpulse});
                livestext->Create(renderer, "HP: "+std::to_string(lives), SDL_Color{255, 255, 255, playerpulse});
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                playerpulse = 255;
                musicgroup->setPaused(true);
                
                //Text drawing
                scoretext->Create(renderer, "FINAL SCORE: "+std::to_string(score), SDL_Color{255, 255, 255, playerpulse});
                livestext->Create(renderer, "GGS", SDL_Color{255, 255, 255, playerpulse});
            }
            if (lives < 2)
            {
                scoretext->Draw(renderer,80+((rand()%3) - 1), 60+((rand()%3) - 1)); livestext->Draw(renderer,win_w-120+((rand()%3) - 1), 60+((rand()%3) - 1));
            }
            else
            {
                scoretext->Draw(renderer,80, 60); livestext->Draw(renderer,win_w-120, 60);
            }
            
            SDL_RenderPresent(renderer);

            onbeat = false;
        }
        
        audio->update();
    }
}

int main(int argc, char* argv[])
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
        return 1;
    }

    // initialize TTF SDL
    if (TTF_Init() < 0)
    {
        std::cerr << "Error initializing SDL TTF: " << SDL_GetError() << "\n";
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
        std::cerr << "Error creating SDL window: " << SDL_GetError() << "\n";
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

    runGame(renderer, audio);
    
    return 0;
}
