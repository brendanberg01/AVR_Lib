//
// Created by Brendan Berg on 2019-04-20.
//

#ifndef ATAR_CENTRAL_EXTERNALINTERRUPTHANDLER_HPP
#define ATAR_CENTRAL_EXTERNALINTERRUPTHANDLER_HPP

#include <avr/interrupt.h>

#include "ExternalInterrupt.hpp"


#if defined(__AVR_ATmega328P__)
#define EXT_INT_NUM 2
extern "C" void INT0_vect(void) __attribute__ ((signal));
extern "C" void INT1_vect(void) __attribute__ ((signal));
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
#define EXT_INT_NUM 8
extern "C" void INT0_vect(void) __attribute__ ((signal));
extern "C" void INT1_vect(void) __attribute__ ((signal));
extern "C" void INT2_vect(void) __attribute__ ((signal));
extern "C" void INT3_vect(void) __attribute__ ((signal));
extern "C" void INT4_vect(void) __attribute__ ((signal));
extern "C" void INT5_vect(void) __attribute__ ((signal));
extern "C" void INT6_vect(void) __attribute__ ((signal));
extern "C" void INT7_vect(void) __attribute__ ((signal));
#endif


class ExternalInterruptHandler
{
public:

    virtual void InterruptServiceRoutine () = 0;


protected:

    ExternalInterruptHandler (uint8_t extIntrptID, uint8_t mode,
                              ExternalInterruptHandler* handler);

    static ExternalInterruptHandler* instancePtr[EXT_INT_NUM];


private:

    ExternalInterrupt m_ExternalInterrupt;


#if defined(__AVR_ATmega328P__)
    friend void INT0_vect();
    friend void INT1_vect();
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
    friend void INT0_vect();
    friend void INT1_vect();
    friend void INT2_vect();
    friend void INT3_vect();
    friend void INT4_vect();
    friend void INT5_vect();
    friend void INT6_vect();
    friend void INT7_vect();
#endif


};


#endif //ATAR_CENTRAL_EXTERNALINTERRUPTHANDLER_HPP
