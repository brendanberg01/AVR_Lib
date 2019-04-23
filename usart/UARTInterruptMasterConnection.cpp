//
// Created by Brendan Berg on 2019-04-21.
//

#include <mcu/usart/UARTInterruptMasterConnection.hpp>


UARTInterruptMasterConnection::UARTInterruptMasterConnection (uint8_t uartID,
                                                              uint32_t baud,
                                                              UARTDataDestination& destination,
                                                              volatile uint8_t* port,
                                                              uint8_t bit)
    : UARTConnection(uartID, baud, destination), m_InterruptPin(port, bit)
{
    m_RequestState = RequestState::null;
}


void UARTInterruptMasterConnection::RequestData ()
{
    if (m_RequestState == RequestState::null)
    {
        m_InterruptPin.Enable();
        m_RequestState = RequestState::pending;
        m_InterruptPin.Disable();
    }
}


bool UARTInterruptMasterConnection::ResponseReceived ()
{
    return MessageReceived();
}


void UARTInterruptMasterConnection::DiscardResponse ()
{
    DiscardMessage();
    m_RequestState = RequestState::null;
}


void UARTInterruptMasterConnection::DispatchMessage ()
{
    m_DataDestination.DispatchMessage(GetMessage(), GetMessageLength());
    DiscardResponse();
}
