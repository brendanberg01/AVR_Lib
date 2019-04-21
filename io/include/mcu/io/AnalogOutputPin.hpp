//
// Created by Brendan Berg on 19.04.19.
//

#ifndef ATAR_CENTRAL_ANALOGOUTPUTPIN_HPP
#define ATAR_CENTRAL_ANALOGOUTPUTPIN_HPP

#include <stdint.h>

#include <mcu/timer/Timer.hpp>


class AnalogOutputPin
{
public:

    AnalogOutputPin(volatile uint8_t* port, uint8_t bit,
                    Timer* timer, uint8_t ocr);

    void SetValue (uint8_t value);


private:

    Timer* m_Timer;

    uint8_t m_OCR;


};


#endif //ATAR_CENTRAL_ANALOGOUTPUTPIN_HPP
