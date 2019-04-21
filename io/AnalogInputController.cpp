//
// Created by Brendan Berg on 22.02.19.
//

#include <mcu/io/AnalogInputController.hpp>


AnalogInputController* AnalogInputController::instancePtr = nullptr;


AnalogInputController::AnalogInputController ()
    : m_RegisteredPins(0), m_SelectedInputPin(0),
    m_AnalogControllerEnabled(false)
{
    // set reference voltage to avcc
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    // set data register to left adjusted
    ADMUX |= (1 << ADLAR);

    // enable adc interrupt
    ADCSRA |= (1 << ADIE);

    // set prescaler to 128x
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    // enable adc
    ADCSRA |= (1 << ADEN);

    AnalogInputController::instancePtr = this;
}


void AnalogInputController::RegisterAnalogPin (AnalogInputPin* pin)
{
    m_AnalogInputPins[m_RegisteredPins] = pin;
    ++m_RegisteredPins;
}


void AnalogInputController::Enable ()
{
    m_AnalogControllerEnabled = true;
    m_SelectedInputPin = 0;
    StartSingleConversion();
}


void AnalogInputController::Disable ()
{
    m_AnalogControllerEnabled = false;
}


void AnalogInputController::StartSingleConversion ()
{
    m_AnalogInputPins[m_SelectedInputPin]->SelectChannel();
    ADCSRA |= (1 << ADSC);
}


void AnalogInputController::ConversionCompleteInterruptServiceRoutine ()
{
    uint8_t value = ADCH;
    m_AnalogInputPins[m_SelectedInputPin]->SetValue(value);

    if (!m_AnalogControllerEnabled)
    {
        return;
    }

    ++m_SelectedInputPin;
    m_SelectedInputPin %= m_RegisteredPins;
    StartSingleConversion();
}


ISR (ADC_vect)
{
    AnalogInputController::instancePtr->
        ConversionCompleteInterruptServiceRoutine();
}
