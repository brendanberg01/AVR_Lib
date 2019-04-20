//
// Created by Brendan Berg on 20.04.19.
//

#ifndef ATAR_CENTRAL_EXTERNALINTERRUPT_HPP
#define ATAR_CENTRAL_EXTERNALINTERRUPT_HPP

#include "ExternalInterruptConfig.hpp"


class ExternalInterrupt
{
public:

    explicit ExternalInterrupt (ExternalInterruptConfig extIntrptCfg);

    void Enable();

    void Disable();


private:

    volatile uint8_t* m_InterruptFlagRegister;

    uint8_t m_InterruptFlagMask;


};


#endif //ATAR_CENTRAL_EXTERNALINTERRUPT_HPP
