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
        SDL_Rect  headleft={192,64,64,64};
        SDL_Rect  headright={256,0,64,64};
        SDL_Rect  headup={192,0,64,64};
        SDL_Rect  headdown={256,64,64,64};
        SDL_Rect  tailright={256,128,64,64};
        SDL_Rect  tailleft={192,192,64,64};
        SDL_Rect  taildown={256,192,64,64};
        SDL_Rect  tailup={192,128,64,64};
        SDL_Rect  bodyvert={128,64,64,64};
        SDL_Rect  bodyhoriz={64,0,64,64};
        SDL_Rect  curl1={0,0,64,64};
        SDL_Rect  curl2={128,0,64,64};
        SDL_Rect  curl3={0,64,64,64};
        SDL_Rect  curl4={128,128,64,64};
        SDL_Rect  null={64,64,64,64};
        int curdir;
        SDL_Rect* getpeice(int x);

        void update();
    public:
        SDL_Texture *spritesheet;
        int initlength=5;
        std::deque<SDL_Point> body;
        std::deque<int> direction;
        int lastdirection;
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
