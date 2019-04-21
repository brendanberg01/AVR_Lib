//
// Created by Passi on 13.02.2019.
//

#include <mcu/io/DigitalInputPin.hpp>


DigitalInputPin::DigitalInputPin (volatile uint8_t* pin, uint8_t bit)
    : m_Pin(pin), m_Bit(bit)
{
    *(m_Pin + 1) &= ~(1 << bit);
}


bool DigitalInputPin::GetState () const
{
    return static_cast<bool>((*m_Pin >> m_Bit) & 1);
}
