#pragma once
#include "Particle.h"

class Star : Particle
{
public:
    FVector2 pos = FVector2(0,0);
    
    Star(FVector2 thispos, FVector2 vel): Particle(thispos, vel) { pos = thispos; }

    bool Update() override
    {
        pos.x += velocity.x; pos.y += velocity.y;
        return false;
    }
    
    void Draw(SDL_Renderer* renderer) override
    {
        SDL_RenderDrawPoint(renderer,pos.x,pos.y);
    }
};
