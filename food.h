/*
*Author:-Pukar Giri
*Created On:-12Th December 2018 at 12:28
*File Name:-food.h
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef DLIBPRAC_FOOD_H
#define DLIBPRAC_FOOD_H
#include "snake.h"
#include <SDL2/SDL.h>


class food
    {
    private:
        snake &snake1;
        void eaten();
        SDL_Renderer *renderer;
    public:
        SDL_Point loc;
        food(SDL_Renderer *renderer,snake &snake1);
        void foodfor(snake &snake1);
        void newfood();
        void draw();

    };



#endif //DLIBPRAC_FOOD_H
