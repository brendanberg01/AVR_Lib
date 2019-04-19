//
// Created by Brendan Berg on 20.04.19.
//

#include <mcu/timer/TimerFastPWM.hpp>


TimerFastPWM::TimerFastPWM (uint8_t timerID, uint16_t prescaler)
    : Timer::Timer(GetModeConfig(timerID, prescaler), timerID)
{ }


TimerModeConfig TimerFastPWM::GetModeConfig (uint8_t timerID,
                                             uint16_t prescaler)
{
    TimerRegisterConfig rgtrCfg(timerID);
    TimerModeConfig modeCfg = {};

    if (rgtrCfg.twoBytes)
    {
        modeCfg.waveform = TimerModeConfig::waveform16PwmFast8bit;
    }
    else
    {
        modeCfg.waveform = TimerModeConfig::waveform8PwmFastMax;
    }

    switch (prescaler)
    {
        default:
        case 1:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs1;
            break;
        case 8:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs8;
            break;
        case 64:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs64;
            break;
        case 256:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs256;
            break;
        case 1024:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs1024;
            break;
    }

    return modeCfg;
}
