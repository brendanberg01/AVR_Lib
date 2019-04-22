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
        case 0x0001:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs1;
            break;
        case 0x0008:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs8;
            break;
        case 0x0040:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs64;
            break;
        case 0x0100:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs256;
            break;
        case 0x0400:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs1024;
            break;
    }

    return modeCfg;
}
