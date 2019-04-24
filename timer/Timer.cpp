//
// Created by Brendan Berg on 19.04.19.
//

#include <mcu/timer/Timer.hpp>


Timer* Timer::instancePtr[TIMER_NUM] = {nullptr};


Timer::Timer (TimerModeConfig modeCfg, uint8_t timerID)
    : Timer(modeCfg, TimerRegisterConfig(timerID), timerID)
{ }


Timer::Timer (TimerModeConfig modeCfg, TimerRegisterConfig rgtrCfg,
              uint8_t timerID)
    : m_RegisterConfig(rgtrCfg), m_ClockSource(0)
{
    Init();
    SetWaveformGeneration(modeCfg);
    SetClockSource(modeCfg);

    instancePtr[timerID] = this;
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


void Timer::EnableCompareMatchInterrupt (uint8_t ocr)
{
    *m_RegisterConfig.timsk |= (1 << (ocr + OCIE0A));
}


void Timer::EnableOverflowInterrupt ()
{
    *m_RegisterConfig.timsk |= (1 << TOIE0);
}


#define CMISR(vect, i, ocr) ISR (vect)\
{\
    Timer::instancePtr[i]->CompareMatchInterrupt(ocr);\
}

#define OISR(vect, i) ISR (vect)\
{\
    Timer::instancePtr[i]->OverflowInterrupt();\
}

#if defined(__AVR_ATmega328P__)
CMISR(TIMER0_COMPA_vect, 0, 0)
CMISR(TIMER0_COMPB_vect, 0, 1)
OISR(TIMER0_OVF_vect, 0)
CMISR(TIMER1_COMPA_vect, 1, 0)
CMISR(TIMER1_COMPB_vect, 1, 1)
OISR(TIMER1_OVF_vect, 1)
CMISR(TIMER2_COMPA_vect, 2, 0)
CMISR(TIMER2_COMPB_vect, 2, 1)
OISR(TIMER2_OVF_vect, 2)
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
CMISR(TIMER0_COMPA_vect, 0, 0)
CMISR(TIMER0_COMPB_vect, 0, 1)
OISR(TIMER0_OVF_vect, 0)
CMISR(TIMER1_COMPA_vect, 1, 0)
CMISR(TIMER1_COMPB_vect, 1, 1)
CMISR(TIMER1_COMPC_vect, 1, 2)
OISR(TIMER1_OVF_vect, 1)
CMISR(TIMER2_COMPA_vect, 2, 0)
CMISR(TIMER2_COMPB_vect, 2, 1)
OISR(TIMER2_OVF_vect, 2)
CMISR(TIMER3_COMPA_vect, 3, 0)
CMISR(TIMER3_COMPB_vect, 3, 1)
CMISR(TIMER3_COMPC_vect, 3, 2)
OISR(TIMER3_OVF_vect, 3)
CMISR(TIMER4_COMPA_vect, 4, 0)
CMISR(TIMER4_COMPB_vect, 4, 1)
CMISR(TIMER4_COMPC_vect, 4, 2)
OISR(TIMER4_OVF_vect, 4)
CMISR(TIMER5_COMPA_vect, 5, 0)
CMISR(TIMER5_COMPB_vect, 5, 1)
CMISR(TIMER5_COMPC_vect, 5, 2)
OISR(TIMER5_OVF_vect, 5)
#endif
