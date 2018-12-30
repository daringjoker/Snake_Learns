/*
*Author:-Pukar Giri
*Created On:-21Th December 2018 at 20:49
*File Name:-snakeai.cpp
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "snakeai.h"
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include "paras.h"
#include <cmath>
#include<SDL2/SDL.h>



typedef struct
    {
        action action1;
        float  value;
    } action_value;



bool operator<(const state state1, const state state2)
    {
        return (
                state1.c1 < state2.c1 &&
                state1.c2 < state2.c2 &&
                state1.c3 < state2.c3 &&
                state1.c4 < state2.c4 &&
                state1.c5 < state2.c5 &&
                state1.c6 < state2.c6 &&
                state1.c7 < state2.c7 &&
                state1.c8 < state2.c8 &&
                state1.x < state2.x &&
                state1.y < state2.y
        );
    }



bool operator>(const state state1, const state state2)
    {
        return (
                state1.c1 > state2.c1 &&
                state1.c2 > state2.c2 &&
                state1.c3 > state2.c3 &&
                state1.c4 > state2.c4 &&
                state1.c5 > state2.c5 &&
                state1.c6 > state2.c6 &&
                state1.c7 > state2.c7 &&
                state1.c8 > state2.c8 &&
                state1.x > state2.x &&
                state1.y > state2.y
        );
    }



bool operator==(const state state1, const state state2)
    {
        return (
                state1.c1 == state2.c1 &&
                state1.c2 == state2.c2 &&
                state1.c3 == state2.c3 &&
                state1.c4 == state2.c4 &&
                state1.c5 == state2.c5 &&
                state1.c6 == state2.c6 &&
                state1.c7 == state2.c7 &&
                state1.c8 == state2.c8 &&
                state1.x == state2.x &&
                state1.y == state2.y
        );
    }



bool operator<(const state_action_pair pair1, const state_action_pair pair2)
    {
        return (pair1.state1 < pair2.state1 && pair1.action1 < pair2.action1);
    }



bool operator>(const state_action_pair pair1, const state_action_pair pair2)
    {
        return (pair1.state1 > pair2.state1 && pair1.action1 > pair2.action1);
    }



bool operator==(const state_action_pair pair1, const state_action_pair pair2)
    {
        return (pair1.state1 == pair2.state1 && pair1.action1 == pair2.action1);
    }



bool comp_action_value(action_value pair1, action_value pair2)
    {
        return pair1.value < pair2.value;
    }



bool comp_key_value(key_value key_value1, key_value key_value2)
    {
        return key_value1.pair < key_value1.pair;
    }



bool comp_reward(float reward1, float reward2)
    {
        return reward1 < reward2;
    }



snakeai::snakeai(snake &snake1, food &food1, float epsilion, float alpha, float gamma) :
        snake1{snake1}, food1{food1}
    {
        this->epsilion = epsilion;
        this->alpha    = alpha;
        this->gamma    = gamma;
    }



inline float snakeai::getq(state_action_pair pair)
    {

        unsigned int x = 0;
        for (auto    item :q)
        {
            if (item.pair == pair)
            {
                break;
            }
            x++;
        }
        if (x >= q.size())return 0.0;
        return q.at(x).value;
    }



void snakeai::setq(state_action_pair pair, float value)
    {
        unsigned int x = 0;
        for (auto    item : q)
        {
            if (item.pair == pair)
            {
                break;
            }
            x++;
        }
        if (x >= q.size())
        {
            q.push_back({pair, value});
            std::sort(q.begin(), q.end(), comp_key_value);
            return;
        }
        q.at(x).value = value;
    }



void snakeai::learnq(state state1, action action1, float reward, float value)
    {
        state_action_pair state_action{state1, action1};
        float             oldvalue = getq(state_action);
        //        if (gencount%1000==0)
        //        {
        //            printf("old value : %f\n", oldvalue);
        //        }
        if (oldvalue == 0)
        {
            //            printf("found new state \n");
            setq(state_action, reward);
            //            q.insert(std::make_pair(state_action,reward));
        }
        else
        {
            this->setq(state_action, oldvalue + this->alpha * (value - oldvalue));
        }
    }



action snakeai::chooseaction(state state1)
    {
        if ((random() % 100) < this->epsilion)
        {
            //            printf("choosing randomly\n");
            switch (random() % 4)
            {
                case 0:
                    return action::left;
                case 1:
                    return action::right;
                case 2:
                    return action::up;
                case 3:
                    return action::down;
                default:
                    return action::none;
            }
        }
        std::vector<action_value> qvals;
        qvals.push_back({action::down, this->getq({state1, action::down})});
        qvals.push_back({action::up, this->getq({state1, action::up})});
        qvals.push_back({action::left, this->getq({state1, action::left})});
        qvals.push_back({action::right, this->getq({state1, action::right})});
        qvals.push_back({action::none, this->getq({state1, action::none})});
        action_value *x, *y;
        std::sort(qvals.begin(), qvals.end(), comp_action_value);
        std::vector<action_value> maxqs;
        if (gencount % 1010 == 0)
        {
            for (auto item :qvals)
            {
                printf("%f\t", item.value);
            }
            printf("\n");
        }
        for (auto                 qs :qvals)
        {
            if (qs.value == qvals[0].value)
            {
                maxqs.push_back(qs);
            }
        }
        unsigned long             index = random() % maxqs.size();
        if (gencount % 1000 == 0)
        {
            printf("max q value: %f\nmin q value : %f \n", maxqs[index].value, qvals[qvals.size() - 1].value);
        }
        return maxqs[index].action1;
    }



void snakeai::learn(state state1, action action1, float reward, state state2)
    {
        std::vector<float> qvals;
        qvals.push_back(this->getq({state1, action::down}));
        qvals.push_back(this->getq({state1, action::up}));
        qvals.push_back(this->getq({state1, action::left}));
        qvals.push_back(this->getq({state1, action::right}));
        qvals.push_back(this->getq({state1, action::none}));
        std::sort(qvals.begin(), qvals.end(), comp_reward);
        float maxqnew = qvals[0];
        this->learnq(state1, action1, reward, reward + this->gamma * maxqnew);
    }



inline state_action_pair snakeai::get_state_action_pair(state &state1, action &action1)
    {
        return state_action_pair{state1, action1};
    }



state snakeai::calc_state(double headdist)
    {
        int_fast8_t state_id[9];
        int_fast8_t index = 0;
        for (int    i     = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                bool calculated = false;
                if (i == 0 && j == 0) continue;
                int x = snake1.headpos().x + i * BLK_SIZE;
                int y = snake1.headpos().y + j * BLK_SIZE;
                if (x > WINW - BLK_SIZE)x = 0;
                if (y > WINH - BLK_SIZE)y = 0;
                if (x < 0)x               = WINW - BLK_SIZE;
                if (y < 0)y               = WINH - BLK_SIZE;
                for (auto point :snake1.body)
                {
                    if (x == point.x && y == point.y)
                    {
                        state_id[index] = 0;
                        calculated = true;
                    }
                }
                if (food1.loc.x == x && food1.loc.y == y)
                {
                    state_id[index] = 2;
                    calculated = true;
                }
                if (!calculated)
                {
                    double newdist = sqrt(pow(x - food1.loc.x, 2) + pow(y - food1.loc.y, 2));
                    if (newdist <= headdist)
                    {
                        state_id[index] = 1;
                    }
                    else
                    {
                        state_id[index] = -1;
                    }
                }
                //                printf("sate id no %d is %d\n",index,state_id[index]);
                index++;
            }
        }
        return {
                state_id[0], state_id[1], state_id[2], state_id[3], state_id[4], state_id[5], state_id[6], state_id[7],
                snake1.xdir, snake1.ydir
        };
    }



float snakeai::calc_reward(double headdist, int none_count)
    {
        float reward = 0;
        if(lastaction!=action::none){
//            reward-;
        }
        if (headdist > lastdist)
        {
            reward = -500;
        }
        else
        {
            reward += 500 * none_count;
        }
        if (headdist <= lastdist)
        {
            reward += 5000;
        }
        if (snake1.headpos().x == food1.loc.x && snake1.headpos().y == food1.loc.y)
        {
            reward += 500;
            eatcount++;
        }
        if (snake1.died)
        {
            snake1.died = false;
            deathcount++;
            reward -= 50000;
        }
        if (snake1.dropped)
        {
            snake1.dropped = false;
            reward += -500;
            dropcount++;
        }
        //        printf("reward: %f \n",reward);
        return -reward;
    }



void snakeai::drivesnake()
    {
        double headdist = sqrt(pow(snake1.headpos().x - food1.loc.x, 2) + pow(snake1.headpos().y - food1.loc.y, 2));
        state  newstate = calc_state(headdist);
        action action1  = chooseaction(newstate);
//                if(gencount>50000){
//                    this->speed=25;
//                    snake1.initlength=5;
//                    this->epsilion=5;
//                }
        if (gencount % 1000 == 0)
        {
            system("clear");
            printf("turncount:- %lld \nstate:- {%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}\n", this->gencount, newstate.c1,
                   newstate.c2, newstate.c3, newstate.c4, newstate.c5, newstate.c6, newstate.c7, newstate.c8,
                   newstate.x, newstate.y);
            printf("eatcount   : %lld\n", eatcount);
            printf("deathcount : %lld\n", deathcount);
            printf("dropcount  : %lld\n", dropcount);
            printf("down count         : %lld\n", no_of_down_choosen);
            printf("up count           : %lld\n", no_of_up_choosen);
            printf("left count         : %lld\n", no_of_left_choosen);
            printf("right count        : %lld\n", no_of_right_choosen);
            printf("none choosen count : %lld\n", no_of_none_choosen);
            printf("q length : %d s \n", q.size());
            printf("q size : %ld Bytes \n", q.size() * sizeof(key_value));
            printf("q size : %f KB \n", q.size() * sizeof(key_value) / 1024.0);
            printf("=======================================================\n\n");
            //            printf("actionchoosen : %d\n\n", action1);

        }
        switch (action1)
        {
            case action::left:
                snake1.moveleft();
                no_of_left_choosen++;
                nonecount = 0;
                break;
            case action::right:
                snake1.moveright();
                no_of_right_choosen++;
                nonecount = 0;
                break;
            case action::up:
                no_of_up_choosen++;
                snake1.moveup();
                nonecount = 0;
                break;
            case action::down:
                snake1.movedown();
                no_of_down_choosen++;
                nonecount = 0;
                break;
            case action::none:
                no_of_none_choosen++;
                nonecount++;
                break;
        }
        if (gencount)
        {
            learn(laststate, lastaction, calc_reward(headdist, nonecount), newstate);
        }
        lastdist   = headdist;
        lastaction = action1;
        laststate  = newstate;
        gencount++;
    }
