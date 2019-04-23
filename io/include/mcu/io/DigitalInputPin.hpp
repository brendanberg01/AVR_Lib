//
// Created by Passi on 13.02.19.
//

#ifndef AVR_LIB_DIGITALINPUTPIN_HPP
#define AVR_LIB_DIGITALINPUTPIN_HPP

#include <stdint.h>


class DigitalInputPin
{
public:

    DigitalInputPin();

    DigitalInputPin (volatile uint8_t* pin, uint8_t bit);

    bool GetState () const;


private:

    volatile uint8_t* m_Pin;

    uint8_t m_Bit;


};


#endif //AVR_LIB_DIGITALINPUTPIN_HPP
