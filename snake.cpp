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



enum dirn
    {
        up, down, left, right, none
    };



snake::snake(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
        for (int x = 0; x < initlength; ++x)
        {
            SDL_Point defbody1 = {0, x * BLK_SIZE};
            body.push_back(defbody1);
            direction.push_back(none);
        }

        //body.push_back(defbody2);
        this->xdir = 0;
        this->ydir = 0;
        SDL_Surface *surf = SDL_LoadBMP("../snake-graphics.bmp");
        spritesheet = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }



void snake::die()
    {
        this->died = true;
        SDL_Point head  = body[0];
        int       dirn1 = direction[0];
        body.clear();
        direction.clear();
        direction.push_back(dirn1);
        curdir=none;
        body.push_back(head);
        this->xdir = 0;
        this->ydir = 0;
        for (int x = 0; x < initlength; x++)
        {
            this->grow();
        }
    }



void snake::update()
    {
        body.pop_back();
        direction.pop_back();
        if (body.at(0).x > WINW - BLK_SIZE)body[0].x = 0;
        if (body.at(0).y > WINH - BLK_SIZE)body[0].y = 0;
        if (body.at(0).x < 0)body[0].x               = WINW - BLK_SIZE;
        if (body.at(0).y < 0)body[0].y               = WINH - BLK_SIZE;
        body.push_front({body.at(0).x + (this->xdir * BLK_SIZE), body.at(0).y + (this->ydir * BLK_SIZE)});
        direction.push_front(curdir);
        for (int x = 1; x < body.size(); x++)
        {
            if (body.at(x).x == body.at(0).x && body.at(x).y == body.at(0).y)
            {
                this->die();
            }
        }
    }



void snake::draw()
    {
        //std::cout << "entered draw function" << std::endl;
        for (int x = 0; x < body.size(); x++)
        {
            //std::cout << point.y << " " << point.x << std::endl;
            SDL_Rect rect1  = {body[x].x, body[x].y, BLK_SIZE, BLK_SIZE};
            //            SDL_SetRenderDrawColor(renderer, 150, 0, 0, 50);
            //            SDL_RenderDrawRect(renderer, &rect1);
            //            SDL_RenderFillRect(renderer, &rect1);
            SDL_Rect *srect = getpeice(x);
            lastdirection = direction[x];
            SDL_RenderCopy(renderer, spritesheet, srect, &rect1);
        }
        this->update();
    }



void snake::grow()
    {
        body.push_front({body.at(0).x + (this->xdir * BLK_SIZE), body.at(0).y + (this->ydir * BLK_SIZE)});
        direction.push_front(curdir);
    }



SDL_Point snake::headpos()
    {
        return body.at(0);
    }



void snake::moveup()
    {
        if (ydir)
        {
            dropped = true;
            return;
        }
        //        std::cout << "moving it up" << std::endl;
        this->xdir = 0;
        this->ydir = -1;
        curdir = up;
    }



void snake::movedown()
    {
        if (ydir)
        {
            dropped = true;
            return;
        }
        //        std::cout << "moving it down" << std::endl;
        this->xdir = 0;
        this->ydir = 1;
        curdir = down;
    }



void snake::moveleft()
    {
        if (xdir)
        {
            dropped = true;
            return;
        }
        //        std::cout << "moving it left" << std::endl;
        this->xdir = -1;
        this->ydir = 0;
        curdir = left;
    }



void snake::moveright()
    {
        //        std::cout << "moving it right" << std::endl;
        if (xdir)
        {
            dropped = true;
            return;
        }
        this->xdir = 1;
        this->ydir = 0;
        curdir = right;
    }



SDL_Rect *snake::getpeice(int x)
    {
        if (x == 0)
        {
            //            printf("%d\n",direction[0]);
            //            printf("%d\n",curdir);
            switch (direction[0])
            {
                case up:
                    return &headup;
                case down:
                    return &headdown;
                case left:
                    return &headleft;
                case right:
                    return &headright;
                default:
                    return &null;
            }
        }
        if (x == direction.size() - 1)
        {
            switch (lastdirection)
            {
                case up:
                    return &tailup;
                case down:
                    return &taildown;
                case left:
                    return &tailleft;
                case right:
                    return &tailright;
                default:
                    return &null;
            }
        }
        if (lastdirection == direction[x])
        {
            if (lastdirection == left || lastdirection == right)return &bodyhoriz;
            if (lastdirection == up || lastdirection == down) return &bodyvert;
        }
        if (direction[x] == left)
        {
            if (lastdirection == down)return &curl1;
            if (lastdirection == up)return &curl3;
        }
        if (direction[x] == right)
        {
            if (lastdirection == down)return &curl2;
            if (lastdirection == up)return &curl4;
        }
        if (direction[x] == up)
        {
            if (lastdirection == left)return &curl2;
            if (lastdirection == right)return &curl1;
        }
        if (direction[x] == down)
        {
            if (lastdirection == left)return &curl4;
            if (lastdirection == right)return &curl3;
        }
        return &null;
    }
