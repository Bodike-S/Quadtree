#pragma once
#include "Rectangle.h"
#include<math.h>
#define SPEED 2.0f
#define PI 3.14159265
class Entity :
    public Rectangle
{
private:
    float SCREEN_W = 600;
    float SCREEN_H = 800;
public:
    bool collides;
    float angle;
        
    Entity(float _x, float _y, float _w, float _h) :
        Rectangle(_x,_y,_w,_h), collides(false), angle(0){}

    void setScreenSize(float w, float h)
    {
        SCREEN_W = w;
        SCREEN_H = h;
    }
    void Move()
    {
        srand(time(0));
        x += cos(angle / 180 * PI) * SPEED;
        y += sin(angle / 180 * PI) * SPEED;

        if (x < w)
        {
            x = w;
            angle = 180 - angle;
            angle += rand() % 21 - 10;
        }
        else if (x > SCREEN_W - w)
        {
            x = SCREEN_W - w;
            angle = 180 - angle;
            angle += rand() % 21 - 10;
        }
        if (y < h)
        {
            y = h;
            angle = -angle;
            angle += rand() % 21 - 10;
        }
        else if (y > SCREEN_H - h)
        {
            y = SCREEN_H - h;
            angle = -angle;
            angle += rand() % 21 - 10;
        }
    }
};

