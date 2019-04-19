//
// Created by Passi on 13.02.2019.
//

#include <mcu/io/DigitalInputPin.hpp>


DigitalInputPin::DigitalInputPin (volatile uint8_t* pin, uint8_t bit)
    : m_Pin(pin), m_Bit(bit)
{
    m_Mask = static_cast<uint8_t>(1) << bit;
    *(m_Pin + 1) &= ~m_Mask;
}


bool DigitalInputPin::Get () const
{
    return static_cast<bool>(*m_Pin >> m_Bit & 1);
}
