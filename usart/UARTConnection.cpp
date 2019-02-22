//
// Created by Brendan Berg on 14.02.19.
//

#include <mcu/usart/UARTConnection.hpp>


UARTConnection* UARTConnection::instancePtr[UART_NUM] = {nullptr};


UARTConnection::UARTConnection (uint8_t uartID, uint32_t baud)
    : m_OngoingTransmission(false)
{
    UARTProtocolConfig uartPrtclCfg = {};
    uartPrtclCfg.cpuFreq       = 16000000;
    uartPrtclCfg.baudFreq      = baud;
    uartPrtclCfg.characterSize = UARTProtocolConfig::characterSize8;
    uartPrtclCfg.parityBit     = UARTProtocolConfig::parityBitOdd;
    uartPrtclCfg.stopBits      = UARTProtocolConfig::stopBits1;
    uartPrtclCfg.doubleSpeedOp = UARTProtocolConfig::doubleSpeedOpDisabled;

    m_UART = UART(uartPrtclCfg, uartID);

    m_UART.EnableReceiveCompleteInterrupt();
    m_UART.EnableTransmitCompleteInterrupt();

    UARTConnection::instancePtr[uartID] = this;
}


bool UARTConnection::DataAvailable ()
{
    return !m_ReceiveBuffer.IsEmpty();
}


uint8_t UARTConnection::ReadByte ()
{
    auto data = m_ReceiveBuffer.Read();
    m_ReceiveBuffer.Pop();
    return data;
}


void UARTConnection::WriteByte (uint8_t data)
{
    m_TransmitBuffer.Push(data);
    if (!m_OngoingTransmission)
    {
        m_OngoingTransmission = true;
        StartTransmission();
    }
}


void UARTConnection::WriteString (const char data[])
{
    auto len = strlen(data);
    for (int i = 0; i < len; ++i)
    {
        WriteByte(static_cast<uint8_t>(data[i]));
    }
}


void UARTConnection::StartTransmission ()
{
    TransmitCompleteInterruptServiceRoutine();
}


void UARTConnection::ReceiveCompleteInterruptServiceRoutine ()
{
    auto data = static_cast<uint8_t>(m_UART.Receive());
    m_ReceiveBuffer.Push(data);
}


void UARTConnection::TransmitCompleteInterruptServiceRoutine ()
{
    if (m_TransmitBuffer.IsEmpty())
    {
        m_OngoingTransmission = false;
        return;
    }

    if (!m_UART.DataRegisterEmpty())
    {
        return;
    }

    auto data = m_TransmitBuffer.Read();
    m_TransmitBuffer.Pop();
    m_UART.Transmit(data);
}


#ifdef UDR0
ISR(USART0_RX_vect)
{
    UARTConnection::instancePtr[0]->ReceiveCompleteInterruptServiceRoutine();
}
ISR(USART0_TX_vect)
{
    UARTConnection::instancePtr[0]->TransmitCompleteInterruptServiceRoutine();
}
#endif

#ifdef UDR1
ISR(USART1_RX_vect)
{
    UARTConnection::instancePtr[1]->ReceiveCompleteInterruptServiceRoutine();
}
ISR(USART1_TX_vect)
{
    UARTConnection::instancePtr[1]->TransmitCompleteInterruptServiceRoutine();
}
#endif

#ifdef UDR2
ISR(USART2_RX_vect)
{
    UARTConnection::instancePtr[2]->ReceiveCompleteInterruptServiceRoutine();
}
ISR(USART2_TX_vect)
{
    UARTConnection::instancePtr[2]->TransmitCompleteInterruptServiceRoutine();
}
#endif

#ifdef UDR3
ISR(USART3_RX_vect)
{
    UARTConnection::instancePtr[3]->ReceiveCompleteInterruptServiceRoutine();
}
ISR(USART3_TX_vect)
{
    UARTConnection::instancePtr[3]->TransmitCompleteInterruptServiceRoutine();
}
#endif
