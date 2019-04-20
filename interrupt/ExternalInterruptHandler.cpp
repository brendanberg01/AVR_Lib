//
// Created by Brendan Berg on 2019-04-20.
//

#include <mcu/interrupt/ExternalInterruptHandler.hpp>


extern "C" void __cxa_pure_virtual() {}


ExternalInterruptHandler* ExternalInterruptHandler::instancePtr[EXT_INT_NUM] =
    {nullptr};


ExternalInterruptHandler::ExternalInterruptHandler (
    uint8_t extIntrptID, uint8_t mode, ExternalInterruptHandler* handler)
    : m_ExternalInterrupt(ExternalInterruptConfig(extIntrptID, mode))
{
    ExternalInterruptHandler::instancePtr[extIntrptID] = handler;
    m_ExternalInterrupt.Enable();
}


#define EIISR(vect, i) ISR (vect)\
{\
    ExternalInterruptHandler::instancePtr[i]->InterruptServiceRoutine();\
}

#if defined(__AVR_ATmega328P__)
EIISR(INT0_vect, 0)
EIISR(INT1_vect, 1)
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
EIISR(INT0_vect, 0)
EIISR(INT1_vect, 1)
EIISR(INT2_vect, 2)
EIISR(INT3_vect, 3)
EIISR(INT4_vect, 4)
EIISR(INT5_vect, 5)
EIISR(INT6_vect, 6)
EIISR(INT7_vect, 7)
#endif
