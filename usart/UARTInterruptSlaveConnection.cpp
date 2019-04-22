//
// Created by Brendan Berg on 2019-04-22.
//

#include <mcu/usart/UARTInterruptSlaveConnection.hpp>


UARTInterruptSlaveConnection::UARTInterruptSlaveConnection (
    uint8_t uartId, uint32_t baud, uint8_t extIntrptId,
    UARTDataSource& dataSource)
    : UARTConnection(uartId, baud),
    ExternalInterruptHandler(extIntrptId,
                             ExternalInterruptConfig::senseControlModeRising,
                             this),
    m_DataSource(dataSource)
{ }


void UARTInterruptSlaveConnection::InterruptServiceRoutine ()
{
    SendData(m_DataSource);
}
