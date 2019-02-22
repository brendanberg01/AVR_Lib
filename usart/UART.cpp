//
// Created by Brendan Berg on 13.02.19.
//

#include <mcu/usart/UART.hpp>


UART::UART ()
    : m_RegisterConfig(0), m_UsesNinthBit(false)
{ }


UART::UART (UARTProtocolConfig& prtclCfg, uint8_t usartID)
    : UART(prtclCfg, UARTRegisterConfig(usartID))
{ }


UART::UART (UARTProtocolConfig& prtclCfg, UARTRegisterConfig rgtrCfg)
    : m_RegisterConfig(rgtrCfg), m_UsesNinthBit(false)
{
    Init();
    SetBaudRate(prtclCfg);
    SetSpeedMode(prtclCfg);
    SetCharacterSize(prtclCfg);
    SetParityMode(prtclCfg);

    Enable();
}


void UART::Enable ()
{
    *m_RegisterConfig.ucsrb |= (1 << RXEN0) | (1 << TXEN0);
}


void UART::EnableReceiveCompleteInterrupt ()
{
    *m_RegisterConfig.ucsrb |= (1 << RXCIE0);
}


void UART::EnableTransmitCompleteInterrupt ()
{
    *m_RegisterConfig.ucsrb |= (1 << TXCIE0);
}


void UART::EnableDataRegisterEmptyInterrupt ()
{
    *m_RegisterConfig.ucsrb |= (1 << UDRIE0);
}


void UART::Transmit (uint16_t data)
{
    while (!(*m_RegisterConfig.ucsra & (1 << UDRE0)));

    if (m_UsesNinthBit)
    {
        if (data & 0x0100)
        {
            *m_RegisterConfig.ucsrb |= (1 << TXB80);
        }
        else
        {
            *m_RegisterConfig.ucsrb &= ~(1 << TXB80);
        }
    }

    *m_RegisterConfig.udr = static_cast<uint8_t>(data & 0x00ff);
}


uint16_t UART::Receive ()
{
    while (!(*m_RegisterConfig.ucsra & (1 << RXC0)));

    uint16_t word = 0;

    if (m_UsesNinthBit)
    {
        word = static_cast<uint16_t>(
            ((*m_RegisterConfig.ucsrb >> RXB80) & 1) << 8);
    }

    auto errorMask = static_cast<uint8_t>(
        (1 << FE0) | (1 << DOR0) | (1 << UPE0));

    if (*m_RegisterConfig.ucsra & errorMask)
    {
        word |= static_cast<uint16_t>(1 << 15);
    }

    word |= *m_RegisterConfig.udr;

    return word;
}


bool UART::ReceiveComplete () const
{
    return static_cast<bool>(*m_RegisterConfig.ucsra >> RXC0 & 1);
}


bool UART::TransmitComplete () const
{
    return static_cast<bool>(*m_RegisterConfig.ucsra >> TXC0 & 1);
}


bool UART::DataRegisterEmpty () const
{
    return static_cast<bool>(*m_RegisterConfig.ucsra >> UDRE0 & 1);
}


void UART::Init ()
{
    *m_RegisterConfig.udr   = 0;
    *m_RegisterConfig.ucsra = 0;
    *m_RegisterConfig.ucsrb = 0;
    *m_RegisterConfig.ucsrc = 0;
    *m_RegisterConfig.ubrrh = 0;
    *m_RegisterConfig.ubrrl = 0;
}


void UART::SetBaudRate (UARTProtocolConfig& prtclCfg)
{
    auto prescaler = static_cast<uint8_t>(prtclCfg.doubleSpeedOp ? 8 : 16);

    auto baudRegisterValue = static_cast<uint16_t>(
        prtclCfg.cpuFreq / prtclCfg.baudFreq / prescaler - 1);

    *m_RegisterConfig.ubrrh = static_cast<uint8_t>(baudRegisterValue >> 8);
    *m_RegisterConfig.ubrrl = static_cast<uint8_t>(baudRegisterValue & 0xff);
}


void UART::SetSpeedMode (UARTProtocolConfig& prtclCfg)
{
    if (prtclCfg.doubleSpeedOp == UARTProtocolConfig::doubleSpeedOpDisabled)
    {
        *m_RegisterConfig.ucsra |= (1 << U2X0);
    }
}


void UART::SetCharacterSize (UARTProtocolConfig& prtclCfg)
{
    *m_RegisterConfig.ucsrc |= ((prtclCfg.characterSize >> 0) & 1) << UCSZ00;
    *m_RegisterConfig.ucsrc |= ((prtclCfg.characterSize >> 1) & 1) << UCSZ01;
    *m_RegisterConfig.ucsrb |= ((prtclCfg.characterSize >> 2) & 1) << UCSZ02;

    m_UsesNinthBit = static_cast<bool>((prtclCfg.characterSize >> 2) & 1);
}


void UART::SetParityMode (UARTProtocolConfig& prtclCfg)
{
    *m_RegisterConfig.ucsrc |= ((prtclCfg.parityBit >> 0) & 1) << UPM00;
    *m_RegisterConfig.ucsrc |= ((prtclCfg.parityBit >> 1) & 1) << UPM01;
}
