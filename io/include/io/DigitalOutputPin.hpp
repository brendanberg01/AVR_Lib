//
// Created by Brendan Berg on 12.02.19.
//

#ifndef AVR_LIB_DIGITALOUTPUTPIN_HPP
#define AVR_LIB_DIGITALOUTPUTPIN_HPP

#include <cstdint>


class DigitalOutputPin
{
public:

    DigitalOutputPin (uint8_t& port, uint8_t& bit);

    void Enable ();

    void Disable ();

    void Flip ();

    void Set (bool state);

    bool GetState () const;


private:

    uint8_t& m_Port;

    uint8_t m_Mask;

    uint8_t m_MaskInv;

    bool m_State;

};


#endif //AVR_LIB_DIGITALOUTPUTPIN_HPP
