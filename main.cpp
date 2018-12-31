/*
*Author:-Pukar Giri
*Created On:-11Th December 2018 at 19:30
*File Name:-main.cpp
*Project Name:-snake
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/
#include <iostream>
#include <SDL2/SDL.h>
#include "snake.h"
#include "food.h"
#include "paras.h"
#include "snakeai.h"



bool running = true;

void handle_events(SDL_Window *win, snake &snake1);



int main()
    {
        srand(time(0));
        SDL_Init(SDL_INIT_EVERYTHING);//initialize everything from sdl
        SDL_Window   *window   = SDL_CreateWindow("Snake:machine learns it", SDL_WINDOWPOS_CENTERED,
                                                  SDL_WINDOWPOS_CENTERED, WINW, WINH,
                                                  SDL_WINDOW_SHOWN);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Surface *surface=SDL_LoadBMP("../grass.bmp");
        SDL_Texture *grass=SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
        snake snake1(renderer);
        food food1(renderer,snake1);
        snakeai snakedriver(snake1,food1);
        int gencount=0;
        SDL_Rect srect={0,0,512,512};

        while (running)
        {
            handle_events(window,snake1);
            for (int row=0;row*80<=WINW;row++)
            {
                for (int col=0;col*80<=WINH;col++)
                {
                    SDL_Rect drect={row*80,col*80,80,80};
                    SDL_RenderCopy(renderer, grass, &srect,&drect);
                }
            }
            snakedriver.drivesnake();
//            if (gencount%4==0)
//            {
//                gencount=0;
//                snakedriver.drivesnake();
//            }

            gencount++;
            food1.draw();
            snake1.draw();
            SDL_RenderPresent(renderer);
            SDL_Delay(1000/SPEED);
        }
    }



void handle_events(SDL_Window *win,snake &snake1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
//                    std::cout<<"key press detected"<<std::endl;
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
//                            std::cout << "moving up" << std::endl;
                            snake1.moveup();
                            break;
                        case SDLK_DOWN:
//                            std::cout << "moving down" << std::endl;
                            snake1.movedown();
                            break;
                        case SDLK_RIGHT:
//                            std::cout << "moving right" << std::endl;
                            snake1.moveright();
                            break;
                        case SDLK_LEFT:
//                            std::cout << "moving left" << std::endl;
                            snake1.moveleft();
                            break;
                            case SDLK_w:
//                            std::cout << "moving up" << std::endl;
                            snake1.moveup();
                            break;
                        case SDLK_s:
//                            std::cout << "moving down" << std::endl;
                            snake1.movedown();
                            break;
                        case SDLK_d:
//                            std::cout << "moving right" << std::endl;
                            snake1.moveright();
                            break;
                        case SDLK_a:
//                            std::cout << "moving left" << std::endl;
                            snake1.moveleft();
                            break;
                    }
                }
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
    }
