/*
*Author:-Pukar Giri
*Created On:-11Th December 2018 at 21:05
*File Name:-snake.cpp
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "snake.h"
#include "paras.h"
#include <iostream>



snake::snake(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
        for (int x = 0; x < initlength; ++x)
        {
            SDL_Point defbody1 = {100, x * 10};
            body.push_back(defbody1);
        }

        //body.push_back(defbody2);
        this->xdir = 0;
        this->ydir = 0;
    }

void snake::die()
    {
        this->died=true;
        SDL_Point head=body[0];
        body.clear();
        body.push_back(head);
        this->xdir=0;
        this->ydir=0;
        for ( int x =0;x<initlength;x++)
        {
            this->grow();
        }

    }

void snake::update()
    {
        body.pop_back();
        if (body.at(0).x > WINW-BLK_SIZE)body[0].x=0;
        if (body.at(0).y > WINH-BLK_SIZE)body[0].y=0;
        if (body.at(0).x < 0)body[0].x=WINW-BLK_SIZE;
        if (body.at(0).y < 0)body[0].y=WINH-BLK_SIZE;
        body.push_front({body.at(0).x + (this->xdir * BLK_SIZE), body.at(0).y + (this->ydir * BLK_SIZE)});
        for (int x=1;x<body.size();x++)
        {
            if (body.at(x).x==body.at(0).x&&body.at(x).y==body.at(0).y)
            {
                this->die();
            }
        }
    }



//bool snake::outofbound(int x) const
//    {
//        if (body.at(x).x > WINW)body[x].x=0;
//        if (body.at(x).y > WINH)body[x].y=0;
//        if (body.at(x).x < 0)body[x].x=WINW;
//        if (body.at(x).y < 0)body[x].y=WINH;
//    }



void snake::draw()
    {
        //std::cout << "entered draw function" << std::endl;
        for (auto point : body)
        {
            //std::cout << point.y << " " << point.x << std::endl;
            SDL_Rect rect1 = {point.x, point.y, BLK_SIZE, BLK_SIZE};
            SDL_SetRenderDrawColor(renderer, 150, 0, 0, 50);
            SDL_RenderDrawRect(renderer, &rect1);
            SDL_RenderFillRect(renderer, &rect1);

        }
        this->update();
    }



void snake::grow()
    {
        body.push_front({body.at(0).x + (this->xdir * BLK_SIZE), body.at(0).y + (this->ydir * BLK_SIZE)});
    }



SDL_Point snake::headpos()
    {
        return body.at(0);
    }



void snake::moveup()
    {
        if (ydir)
        {
            dropped=true;
            return;
        }
//        std::cout << "moving it up" << std::endl;
        this->xdir = 0;
        this->ydir = -1;
    }



void snake::movedown()
    {
        if (ydir)
        {
            dropped=true;
            return;
        }
//        std::cout << "moving it down" << std::endl;
        this->xdir = 0;
        this->ydir = 1;
    }



void snake::moveleft()
    {
        if (xdir)
        {
            dropped=true;
            return;
        }
//        std::cout << "moving it left" << std::endl;
        this->xdir = -1;
        this->ydir = 0;
    }



void snake::moveright()
    {
//        std::cout << "moving it right" << std::endl;
        if (xdir)
        {
            dropped=true;
            return;
        }
        this->xdir = 1;
        this->ydir = 0;
    }
