//
// Created by Brendan Berg on 19.04.19.
//

#include <mcu/timer/TimerConfig.hpp>

#include <mcu/io/AnalogOutputPin.hpp>


AnalogOutputPin::AnalogOutputPin (volatile uint8_t* port, uint8_t bit,
                                  Timer* timer, uint8_t ocr)
    : m_Timer(timer), m_OCR(ocr)
{
    *(port - 1) |=  static_cast<uint8_t>(1) << bit;

    TimerCompareMatchConfig comCfg(
        m_OCR, TimerCompareMatchConfig::compareMatchModeDisable);
    m_Timer->SetCompareMatchMode(comCfg);
    m_Timer->SetOutputCompareRegister(0x00, m_OCR);
}


void AnalogOutputPin::SetValue (uint8_t value)
{
    m_Timer->SetOutputCompareRegister(value, m_OCR);
}
