/*
*Author:-Pukar Giri
*Created On:-21Th December 2018 at 20:49
*File Name:-snakeai.h
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef DLIBPRAC_SNAKEAI_H
#define DLIBPRAC_SNAKEAI_H
#include "snake.h"
#include "food.h"
#include <vector>

typedef struct{
    int_fast8_t c1;
    int_fast8_t c2;
    int_fast8_t c3;
    int_fast8_t c4;
    int_fast8_t c5;
    int_fast8_t c6;
    int_fast8_t c7;
    int_fast8_t c8;
    int_fast8_t x;
    int_fast8_t y;
}state;
enum action{left,right,up,down,none};
typedef struct{
    state state1;
    action action1;
}state_action_pair;
typedef struct{
   state_action_pair pair;
   float value;
}key_value;
////typedef state_action_pair;

class snakeai
    {
    public:
        snake &snake1;
        food &food1;
        std::vector<key_value>q;
        unsigned long long gencount=0;
        unsigned long long eatcount=0;
        unsigned long long deathcount=0;
        unsigned long long no_of_left_choosen=0;
        unsigned long long no_of_right_choosen=0;
        unsigned long long no_of_up_choosen=0;
        unsigned long long no_of_down_choosen=0;
        unsigned long long no_of_none_choosen=0;
        unsigned long long dropcount=0;

        double lastdist;
        state laststate;
        action lastaction;
        int_fast8_t nonecount;
        float epsilion;
        float alpha;
        float gamma;
        void setq(state_action_pair pair,float value);
        inline state_action_pair  get_state_action_pair(state &state1,action & action1);


    public:
        snakeai(snake &snake1,food &food1, float epsilion=4, float alpha=0.6, float gamma=0.9);
        inline float getq(state_action_pair pair);
        void learnq(state state1,action action1,float reward,float value);
        action chooseaction(state);
        void learn(state state1,action action1, float reward,state state2);
        state calc_state(double headdist);
        float calc_reward(double headdist,int none_count);
        void drivesnake();

    };



#endif //DLIBPRAC_SNAKEAI_H
