//
// Created by Brendan Berg on 12.02.19.
//

#include <io/DigitalOutputPin.hpp>


DigitalOutputPin::DigitalOutputPin (uint8_t& port, uint8_t& bit)
    : m_Port(port), m_State(false)
{
    m_Mask = static_cast<uint8_t>(1) << bit;
    m_MaskInv = ~m_Mask;
}


inline void DigitalOutputPin::Enable ()
{
    m_Port |= m_Mask;
    m_State = true;
}


inline void DigitalOutputPin::Disable ()
{
    m_Port &= m_MaskInv;
    m_State = false;
}


inline void DigitalOutputPin::Flip ()
{
    m_Port ^= m_Mask;
    m_State = !m_State;
}


inline void DigitalOutputPin::Set (bool state)
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


inline bool DigitalOutputPin::GetState () const
{
    return m_State;
}
