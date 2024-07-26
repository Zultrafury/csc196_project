#pragma once
#include "FVector2.h"
#include "Vector2.h"
#pragma warning( push )
#pragma warning( disable : 4244 )

class Particle
{
public:
    FVector2 pos = FVector2(0,0);
    FVector2 velocity = FVector2(0,0);
    SDL_Color color;
    int r = 255; int g = 255; int b = 255;
    
    Particle(FVector2 thispos, FVector2 vel)
    {
        pos = thispos;
        velocity = vel;
    }

    Particle(FVector2 thispos, FVector2 vel, int rr, int gg, int bb)
    {
        pos = thispos;
        velocity = vel;
        r = rr; g = gg; b = bb;
    }

    virtual bool Update()
    {
        pos.x += velocity.x; pos.y += velocity.y;
        velocity.x *= 0.99f;
        velocity.y *= 0.99f;
        r--; if (r < 1) { r = 1; }
        g--; if (g < 1) { g = 1; }
        b--; if (b < 1) { b = 1; }
        if (velocity.x < 0.01f && velocity.y < 0.01f)
        {
            return true;
        }
        return false;
    }

    virtual void Draw(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDrawPoint(renderer,pos.x,pos.y);
    }
};

#pragma warning( pop )