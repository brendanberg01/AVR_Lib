//
// Created by Brendan Berg on 2019-04-21.
//

#include <mcu/usart/UARTInterruptMasterConnection.hpp>


UARTInterruptMasterConnection::UARTInterruptMasterConnection (
    uint8_t uartID, uint32_t baud, volatile uint8_t* port, uint8_t bit)
    : UARTConnection(uartID, baud), m_InterruptPin(port, bit),
    m_RequestPending(false), m_ResponseArrived(false), m_MessageLength(0)
{ }


void UARTInterruptMasterConnection::Update ()
{
    while (DataAvailable())
    {
        char nextByte = ReadByte();

        if (m_RequestPending)
        {
            m_Message[m_MessageLength] = nextByte;
            if (nextByte == ControlCharacters::nul)
            {
                m_RequestPending = false;
                m_ResponseArrived = true;
            }
        }
    }
}


void UARTInterruptMasterConnection::RequestData ()
{
    if (m_RequestPending || m_ResponseArrived)
    {
        return;
    }

    m_InterruptPin.Enable();
    m_RequestPending = true;
    m_InterruptPin.Disable();
}


bool UARTInterruptMasterConnection::IsRequestPending ()
{
    return m_RequestPending;
}


bool UARTInterruptMasterConnection::HasResponseArrived ()
{
    return m_ResponseArrived;
}
