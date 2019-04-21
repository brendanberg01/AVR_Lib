//
// Created by Brendan Berg on 22.02.19.
//

#ifndef ATAR_CENTRAL_ANALOGINPUTPIN_HPP
#define ATAR_CENTRAL_ANALOGINPUTPIN_HPP

#include <stdint.h>

#include <mcu/util/Buffer.hpp>

class AnalogInputPin
{
public:

    AnalogInputPin();

    explicit AnalogInputPin (uint8_t pin, uint8_t bufferSize = 1);

    void SelectChannel ();

    void SetValue (uint8_t value);

    uint8_t GetValue ();


private:

    uint8_t m_Pin;

    uint8_t m_BufferSize;

    uint16_t m_ValueSum;

    uint8_t m_ValuesInBuffer;

    Buffer<17> m_ValueBuffer;


};


#endif //ATAR_CENTRAL_ANALOGINPUTPIN_HPP
