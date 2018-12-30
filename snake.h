/*
*Author:-Pukar Giri
*Created On:-11Th December 2018 at 21:05
*File Name:-snake.h
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef DLIBPRAC_SNAKE_H
#define DLIBPRAC_SNAKE_H

#include <deque>
#include <SDL2/SDL.h>
class snake
    {
    private:
        SDL_Renderer *renderer;

        void update();
    public:
        int initlength=5;
        std::deque<SDL_Point> body;
        bool dropped=false;
        int_fast8_t xdir;
        int_fast8_t ydir;
        explicit snake(SDL_Renderer *renderer);
        bool died=false;
        void draw();
        void grow();
        void die();
        void moveup();
        void movedown();
        void moveleft();
        void moveright();
        SDL_Point headpos();
//        bool outofbound(int x) const;
    };



#endif //DLIBPRAC_SNAKE_H
