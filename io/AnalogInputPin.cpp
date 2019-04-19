//
// Created by Brendan Berg on 22.02.19.
//

#include <avr/io.h>
#include <math.h>

#include <mcu/io/AnalogInputPin.hpp>


AnalogInputPin::AnalogInputPin (uint8_t pin, uint8_t bufferSize)
: m_Pin(pin), m_BufferSize(bufferSize), m_ValueSum(0), m_ValuesInBuffer(0)
{
    if (m_BufferSize > 16)
    {
        m_BufferSize = 16;
    }
}


void AnalogInputPin::SelectChannel ()
{
#if defined(__AVR_ATmega328P__)
    ADMUX &= ~(0x0f);
    ADMUX |= (m_Pin & 0x0f);
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX &= ~(0x07);
    ADMUX |= (m_Pin & 0x07);

    ADCSRB &= ~(1 << MUX5);
    ADCSRB |= (((m_Pin & 0x08) >> 3) << MUX5);
#endif
}


void AnalogInputPin::SetValue (uint8_t value)
{
    m_ValueSum += value;

    if (m_ValuesInBuffer < m_BufferSize)
    {
        ++m_ValuesInBuffer;
        m_ValueBuffer.Push(value);
    }
    else
    {
        m_ValueSum -= m_ValueBuffer.Read();
        m_ValueBuffer.Pop();
        m_ValueBuffer.Push(value);
    }
}


uint8_t AnalogInputPin::GetValue ()
{
    return static_cast<uint8_t>(m_ValueSum / m_ValuesInBuffer);
}
