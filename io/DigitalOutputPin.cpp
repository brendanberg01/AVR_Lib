//
// Created by Brendan Berg on 12.02.19.
//

#include <mcu/io/DigitalOutputPin.hpp>


DigitalOutputPin::DigitalOutputPin (volatile uint8_t* port, uint8_t bit)
: m_Port(port), m_State(false)
{
    m_Mask = 1 << bit;
    m_MaskInv = ~m_Mask;
    *(m_Port - 1) |=  m_Mask;
}


void DigitalOutputPin::Enable ()
{
    *m_Port |= m_Mask;
    m_State = true;
}


void DigitalOutputPin::Disable ()
{
    *m_Port &= m_MaskInv;
    m_State = false;
}


void DigitalOutputPin::Flip ()
{
    *m_Port ^= m_Mask;
    m_State = !m_State;
}


void DigitalOutputPin::Set (bool state)
{
    if (state)
    {
        Enable();
    }
    else
    {
        Disable();
    }
}


bool DigitalOutputPin::GetState () const
{
    return m_State;
}
