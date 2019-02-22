//
// Created by Brendan Berg on 13.02.19.
//

#ifndef ATAR_CENTRAL_UART_HPP
#define ATAR_CENTRAL_UART_HPP

#include <stdint.h>
#include <avr/io.h>

#include <mcu/usart/UARTConfig.hpp>


class UART
{
public:

    UART ();

    UART (UARTProtocolConfig& prtclCfg, uint8_t usartID);

    UART (UARTProtocolConfig& prtclCfg, UARTRegisterConfig rgtrCfg);

    void Enable ();

    void EnableReceiveCompleteInterrupt ();

    void EnableTransmitCompleteInterrupt ();

    void EnableDataRegisterEmptyInterrupt ();

    void Transmit (uint16_t data);

    uint16_t Receive ();

    bool ReceiveComplete () const;

    bool TransmitComplete () const;

    bool DataRegisterEmpty () const;


private:

    UARTRegisterConfig m_RegisterConfig;

    bool m_UsesNinthBit;

    void Init ();

    void SetBaudRate (UARTProtocolConfig& prtclCfg);

    void SetSpeedMode (UARTProtocolConfig& prtclCfg);

    void SetCharacterSize (UARTProtocolConfig& prtclCfg);

    void SetParityMode (UARTProtocolConfig& prtclCfg);


};


#endif //ATAR_CENTRAL_UART_HPP
