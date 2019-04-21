//
// Created by Brendan Berg on 22.02.19.
//

#ifndef ATAR_CENTRAL_ANALOGINPUTCONTROLLER_HPP
#define ATAR_CENTRAL_ANALOGINPUTCONTROLLER_HPP

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "AnalogInputPin.hpp"

#if defined(__AVR_ATmega328P__)
    #define ANALOG_PIN_NUM 9
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
    #define ANALOG_PIN_NUM 16
#endif


extern "C" void ADC_vect(void) __attribute__ ((signal));


class AnalogInputController
{
public:

    AnalogInputController ();

    void RegisterAnalogPin (AnalogInputPin* pin);

    void Enable ();

    void Disable ();


private:

    AnalogInputPin* m_AnalogInputPins[ANALOG_PIN_NUM] = {nullptr};

    uint8_t m_RegisteredPins;

    uint8_t m_SelectedInputPin;

    bool m_AnalogControllerEnabled;

    void StartSingleConversion ();

    void ConversionCompleteInterruptServiceRoutine ();

    static AnalogInputController* instancePtr;


    friend void ADC_vect();


};


#endif //ATAR_CENTRAL_ANALOGINPUTCONTROLLER_HPP
