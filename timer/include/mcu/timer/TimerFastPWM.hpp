//
// Created by Brendan Berg on 20.04.19.
//

#ifndef ATAR_CENTRAL_TIMERFASTPWM_HPP
#define ATAR_CENTRAL_TIMERFASTPWM_HPP

#include "Timer.hpp"


class TimerFastPWM : public Timer
{
public:

    TimerFastPWM (uint8_t timerID, uint16_t prescaler);


private:

    static TimerModeConfig GetModeConfig (uint8_t timerID, uint16_t prescaler);


};


#endif //ATAR_CENTRAL_TIMERFASTPWM_HPP
