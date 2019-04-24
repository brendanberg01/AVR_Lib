//
// Created by Brendan Berg on 19.04.19.
//

#ifndef ATAR_CENTRAL_TIMER_HPP
#define ATAR_CENTRAL_TIMER_HPP

#include <stdint.h>
#include <avr/interrupt.h>

#include "TimerConfig.hpp"


#if defined(__AVR_ATmega328P__)
#define TIMER_NUM 3
extern "C" void TIMER0_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER0_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER0_OVF_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_OVF_vect(void) __attribute__ ((signal));
extern "C" void TIMER2_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER2_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER2_OVF_vect(void) __attribute__ ((signal));
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
#define TIMER_NUM 6
extern "C" void TIMER0_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER0_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER0_OVF_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPC_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_OVF_vect(void) __attribute__ ((signal));
extern "C" void TIMER2_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER2_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER2_OVF_vect(void) __attribute__ ((signal));
extern "C" void TIMER3_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER3_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER3_COMPC_vect(void) __attribute__ ((signal));
extern "C" void TIMER3_OVF_vect(void) __attribute__ ((signal));
extern "C" void TIMER4_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER4_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER4_COMPC_vect(void) __attribute__ ((signal));
extern "C" void TIMER4_OVF_vect(void) __attribute__ ((signal));
extern "C" void TIMER5_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER5_COMPB_vect(void) __attribute__ ((signal));
extern "C" void TIMER5_COMPC_vect(void) __attribute__ ((signal));
extern "C" void TIMER5_OVF_vect(void) __attribute__ ((signal));
#endif


class Timer
{
public:

    Timer (TimerModeConfig modeCfg, uint8_t timerID);

    Timer (TimerModeConfig modeCfg, TimerRegisterConfig rgtrCfg,
           uint8_t timerID);

    void SetCompareMatchMode (TimerCompareMatchConfig& comCfg);

    void SetOutputCompareRegister (uint16_t value, uint8_t rgtr);

    void Enable ();

    void Disable ();


protected:

    void Init ();

    void SetWaveformGeneration (TimerModeConfig& modeCfg);

    void SetClockSource (TimerModeConfig& modeCfg);

    void EnableCompareMatchInterrupt (uint8_t ocr);

    virtual void EnableOverflowInterrupt ();

    virtual void CompareMatchInterrupt (uint8_t ocr) {}

    virtual void OverflowInterrupt () {}

    static Timer* instancePtr[TIMER_NUM];


private:

    TimerRegisterConfig m_RegisterConfig;

    uint8_t m_ClockSource;


#if defined(__AVR_ATmega328P__)
    friend void TIMER0_COMPA_vect();
    friend void TIMER0_COMPB_vect();
    friend void TIMER0_OVF_vect();
    friend void TIMER1_COMPA_vect();
    friend void TIMER1_COMPB_vect();
    friend void TIMER1_OVF_vect();
    friend void TIMER2_COMPA_vect();
    friend void TIMER2_COMPB_vect();
    friend void TIMER2_OVF_vect();
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
    friend void TIMER0_COMPA_vect();
    friend void TIMER0_COMPB_vect();
    friend void TIMER0_OVF_vect();
    friend void TIMER1_COMPA_vect();
    friend void TIMER1_COMPB_vect();
    friend void TIMER1_COMPC_vect();
    friend void TIMER1_OVF_vect();
    friend void TIMER2_COMPA_vect();
    friend void TIMER2_COMPB_vect();
    friend void TIMER2_OVF_vect();
    friend void TIMER3_COMPA_vect();
    friend void TIMER3_COMPB_vect();
    friend void TIMER3_COMPC_vect();
    friend void TIMER3_OVF_vect();
    friend void TIMER4_COMPA_vect();
    friend void TIMER4_COMPB_vect();
    friend void TIMER4_COMPC_vect();
    friend void TIMER4_OVF_vect();
    friend void TIMER5_COMPA_vect();
    friend void TIMER5_COMPB_vect();
    friend void TIMER5_COMPC_vect();
    friend void TIMER5_OVF_vect();
#endif


};


#endif //ATAR_CENTRAL_TIMER_HPP
