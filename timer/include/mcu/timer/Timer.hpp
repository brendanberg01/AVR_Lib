//
// Created by Brendan Berg on 19.04.19.
//

#ifndef ATAR_CENTRAL_TIMER_HPP
#define ATAR_CENTRAL_TIMER_HPP

#include <stdint.h>

#include "TimerConfig.hpp"


class Timer
{
public:

    Timer (TimerModeConfig modeCfg, uint8_t timerID);

    Timer (TimerModeConfig modeCfg, TimerRegisterConfig rgtrCfg);

    void SetCompareMatchMode (TimerCompareMatchConfig& comCfg);

    void SetOutputCompareRegister (uint16_t value, uint8_t rgtr);

    void Enable ();

    void Disable ();


private:

    TimerRegisterConfig m_RegisterConfig;

    uint8_t m_ClockSource;

    void Init ();

    void SetWaveformGeneration (TimerModeConfig& modeCfg);

    void SetClockSource (TimerModeConfig& modeCfg);


};


#endif //ATAR_CENTRAL_TIMER_HPP
