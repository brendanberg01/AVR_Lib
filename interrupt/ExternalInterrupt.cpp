//
// Created by Brendan Berg on 20.04.19.
//

#include <mcu/interrupt/ExternalInterrupt.hpp>


ExternalInterrupt::ExternalInterrupt (ExternalInterruptConfig extIntrptCfg)
    : m_InterruptFlagRegister(extIntrptCfg.eimsk), m_InterruptFlagMask(0)
{
    *extIntrptCfg.eicr |=
        (extIntrptCfg.senseControlMode << extIntrptCfg.senseControlBit);

    m_InterruptFlagMask = (1 << extIntrptCfg.requestBit);
}


void ExternalInterrupt::Enable ()
{
    *m_InterruptFlagRegister |= m_InterruptFlagMask;
}


void ExternalInterrupt::Disable ()
{
    *m_InterruptFlagRegister &= ~m_InterruptFlagMask;
}
