//
// Created by Brendan Berg on 20.04.19.
//

#ifndef ATAR_CENTRAL_EXTERNALINTERRUPTCONFIG_HPP
#define ATAR_CENTRAL_EXTERNALINTERRUPTCONFIG_HPP

#include <stdint.h>
#include <avr/io.h>


struct ExternalInterruptConfig
{

    // control register

    volatile uint8_t* eicr;

    uint8_t senseControlBit;

    // request register

    volatile uint8_t* eimsk;

    uint8_t requestBit;

    // sense control mode

    uint8_t senseControlMode;

    static constexpr uint8_t senseControlModeLowLevel = 0x0;
    static constexpr uint8_t senseControlModeChange   = 0x1;
    static constexpr uint8_t senseControlModeFalling  = 0x2;
    static constexpr uint8_t senseControlModeRising   = 0x3;


    ExternalInterruptConfig (uint8_t extIntrptID, uint8_t mode)
    {
#if defined(__AVR_ATmega328P__)
        switch (extIntrptID)
        {
            default:
            case 0:
                eicr = &EICRA;
                senseControlBit = ISC00;
                eimsk = &EIMSK;
                requestBit = INT0;
                break;
            case 1:
                eicr = &EICRA;
                senseControlBit = ISC10;
                eimsk = &EIMSK;
                requestBit = INT1;
                break;
        }
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
        switch (extIntrptID)
        {
            default:
            case 0:
                eicr = &EICRA;
                senseControlBit = ISC00;
                eimsk = &EIMSK;
                requestBit = INT0;
                break;
            case 1:
                eicr = &EICRA;
                senseControlBit = ISC10;
                eimsk = &EIMSK;
                requestBit = INT1;
                break;
            case 2:
                eicr = &EICRA;
                senseControlBit = ISC20;
                eimsk = &EIMSK;
                requestBit = INT2;
                break;
            case 3:
                eicr = &EICRA;
                senseControlBit = ISC30;
                eimsk = &EIMSK;
                requestBit = INT3;
                break;
            case 4:
                eicr = &EICRB;
                senseControlBit = ISC40;
                eimsk = &EIMSK;
                requestBit = INT4;
                break;
            case 5:
                eicr = &EICRB;
                senseControlBit = ISC50;
                eimsk = &EIMSK;
                requestBit = INT5;
                break;
            case 6:
                eicr = &EICRB;
                senseControlBit = ISC60;
                eimsk = &EIMSK;
                requestBit = INT6;
                break;
            case 7:
                eicr = &EICRB;
                senseControlBit = ISC70;
                eimsk = &EIMSK;
                requestBit = INT7;
                break;
        }
#endif

        senseControlMode = mode;
    }


};


#endif //ATAR_CENTRAL_EXTERNALINTERRUPTCONFIG_HPP
