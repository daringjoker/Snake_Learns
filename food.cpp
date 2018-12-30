/*
*Author:-Pukar Giri
*Created On:-12Th December 2018 at 12:28
*File Name:-food.cpp
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "food.h"
#include "paras.h"
#include <random>


void food::eaten()
    {
        if(snake1.headpos().x==this->loc.x&&snake1.headpos().y==this->loc.y)
        {
            newfood();
            snake1.grow();
        }
    }



void food::foodfor(snake &snake1)
    {
        this->snake1=snake1;
    }



void food::newfood()
    {
        this->loc.x=int((random()%(WINW/10))*10);
        this->loc.y=int((random()%(WINW/10))*10);
    }



void food::draw()
    {
        this->eaten();
        SDL_Rect rect1 = {loc.x, loc.y, BLK_SIZE, BLK_SIZE};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 50);
        SDL_RenderDrawRect(renderer, &rect1);
        SDL_RenderFillRect(renderer, &rect1);
    }



food::food(SDL_Renderer *renderer,snake &snake1):
snake1{snake1}
    {
        //this->snake1=snake1;
        this->newfood();
        this->renderer=renderer;
    }
