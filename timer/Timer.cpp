//
// Created by Brendan Berg on 19.04.19.
//

#include <mcu/timer/Timer.hpp>


Timer::Timer (TimerModeConfig modeCfg, uint8_t timerID)
    : Timer(modeCfg, TimerRegisterConfig(timerID))
{ }


Timer::Timer (TimerModeConfig modeCfg, TimerRegisterConfig rgtrCfg)
    : m_RegisterConfig(rgtrCfg)
{
    Init();
    SetWaveformGeneration(modeCfg);
    SetClockSource(modeCfg);
}


void Timer::SetCompareMatchMode (TimerCompareMatchConfig& comCfg)
{
    auto bit = comCfg.outputCompareRegister;
    auto mode = comCfg.compareMatchMode;
    *m_RegisterConfig.tccra |= ((mode >> 0) & 1) << bit;
    *m_RegisterConfig.tccra |= ((mode >> 1) & 1) << (bit + 1);
}


void Timer::SetOutputCompareRegister (uint16_t value, uint8_t rgtr)
{
    volatile uint8_t* ocr = nullptr;
    switch (rgtr)
    {
        default:
        case 0:
            ocr = m_RegisterConfig.ocra;
            break;
        case 1:
            ocr = m_RegisterConfig.ocrb;
            break;
        case 2:
            ocr = m_RegisterConfig.ocrc;
            break;
    }

    *ocr = static_cast<uint8_t>((value & 0x00ff) >> 0);
    if (m_RegisterConfig.twoBytes)
    {
        *(ocr + 1) = static_cast<uint8_t>((value & 0xff00) >> 8);
    }
}


void Timer::Enable ()
{
    Disable();
    *m_RegisterConfig.tccrb |= ((m_ClockSource >> 0) & 1) << CS00;
    *m_RegisterConfig.tccrb |= ((m_ClockSource >> 1) & 1) << CS01;
    *m_RegisterConfig.tccrb |= ((m_ClockSource >> 2) & 1) << CS02;
}


void Timer::Disable ()
{
    *m_RegisterConfig.tccrb &= ~(0x07);
}


void Timer::Init ()
{
    *m_RegisterConfig.tccra = 0;
    *m_RegisterConfig.tccrb = 0;
    *m_RegisterConfig.ocra = 0;
    *m_RegisterConfig.ocrb = 0;

    if (m_RegisterConfig.twoBytes)
    {
        *m_RegisterConfig.ocrc = 0;
    }
}


void Timer::SetWaveformGeneration (TimerModeConfig& modeCfg)
{
    *m_RegisterConfig.tccra |= ((modeCfg.waveform >> 0) & 1) << WGM00;
    *m_RegisterConfig.tccra |= ((modeCfg.waveform >> 1) & 1) << WGM01;
    *m_RegisterConfig.tccrb |= ((modeCfg.waveform >> 2) & 1) << WGM02;

    if (m_RegisterConfig.twoBytes)
    {
        *m_RegisterConfig.tccrb |= ((modeCfg.waveform >> 3) & 1) << WGM13;
    }
}


void Timer::SetClockSource (TimerModeConfig& modeCfg)
{
    m_ClockSource = modeCfg.clockSource;
}
