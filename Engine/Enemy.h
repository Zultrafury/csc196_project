#pragma once
#include <SDL_render.h>
#include <vector>

#include "FVector2.h"
#include "Model.h"

class Enemy
{
public:
    FVector2 center = FVector2(0,0);
    std::vector<FVector2> vectors;
    int behavior = 0; int seed = 0; int sidespawned = 0;
    int lifetime = 0;

    Enemy(FVector2 center_, std::vector<FVector2> vectors_)
    {
        center = center_; vectors = vectors_;
        behavior = rand()%2; seed = rand()%100; 
    }

    Enemy(int w, int h, std::vector<FVector2> vectors_)
    {
        FVector2 center_ = FVector2(-10,-10);
        behavior = rand()%2; seed = rand()%100;
        sidespawned = rand()%4;
        switch (sidespawned)
        {
        case 0:
            center_.x = rand()%(w+1);
            break;
        case 1:
            center_.x = rand()%(w+1);
            center_.y = (h+10);
            break;
        case 2:
            center_.y = rand()%(h+1);
            break;
        case 3:
            center_.y = rand()%(h+1);
            center_.x = (w+10);
            break;
        }
        center = center_; vectors = vectors_;
    }

    bool Update(Model* player, int ticks)
    {
        FVector2 towardsPlayer = FVector2(center.x - player->center.x,center.y - player->center.y);
        switch (behavior)
        {
        case 0:
            center.x -= towardsPlayer.Normalized().x * (1 + (static_cast<float>(seed)/15));
            center.y -= towardsPlayer.Normalized().y * (1 + (static_cast<float>(seed)/15));
            lifetime++;
            break;
        case 1:
            
            switch (sidespawned)
            {
            case 0:
                center.x = (sin(((float)ticks + seed)/35)*600)+600;
                    center.y += 3;
                    break;
            case 1:
                center.x = (sin(((float)ticks + seed)/35)*600)+600;
                    center.y -= 3;
                    break;
            case 2:
                center.x += 3;
                    center.y = (sin(((float)ticks + seed)/35)*450)+450;
                    break;
            case 3:
                center.x -= 3;
                    center.y = (sin(((float)ticks + seed)/35)*450)+450;
                    break;
            }
            lifetime ++;
            break;
        }
        if (lifetime > 12*60)
        {
            return true;
        }
        return false;
    }

    void Draw(SDL_Renderer* renderer)
    {
        for (int i = 1; i < vectors.size(); ++i)
        {
            SDL_RenderDrawLine(renderer,static_cast<int>(vectors[i - 1].x + center.x),static_cast<int>(vectors[i - 1].y + center.y),static_cast<int>(vectors[i].x + center.x),static_cast<int>(vectors[i].y + center.y));
        }
    }
};
