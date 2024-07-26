#pragma once

class FVector2
{
public:
    float x, y;
    
    FVector2(float xx, float yy)
    {
        x = xx; y = yy;
    }

    FVector2 Normalized()
    {
        float magnitude = sqrt(pow(x,2) + pow(y,2));
        return FVector2(x/magnitude,y/magnitude);
    }

    float Magnitude()
    {
        return sqrt(pow(x,2) + pow(y,2));
    }
};