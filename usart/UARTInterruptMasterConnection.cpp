//
// Created by Brendan Berg on 2019-04-21.
//

#include <mcu/usart/UARTInterruptMasterConnection.hpp>


UARTInterruptMasterConnection::UARTInterruptMasterConnection (
    uint8_t uartID, uint32_t baud, volatile uint8_t* port, uint8_t bit)
    : UARTConnection(uartID, baud), m_InterruptPin(port, bit),
    m_MessageLength(0), m_ReceivedMessageLength(0),
    m_RequestState(RequestState::null)
{ }


// TODO: move to UARTConnection and rename to ReceiveData
void UARTInterruptMasterConnection::Update ()
{
    while (DataAvailable())
    {
        char byte = ReadByte();

        switch (m_RequestState)
        {
            case RequestState::null:
                break;
            case RequestState::pending:
                if (byte == ControlCharacters::soh)
                {
                    m_RequestState = RequestState::startOfHeader;
                }
                break;
            case RequestState::startOfHeader:
                m_MessageLength = byte;
                m_RequestState = RequestState::headerReceived;
                break;
            case RequestState::headerReceived:
                if (byte == ControlCharacters::stx)
                {
                    m_RequestState = RequestState::startOfText;
                }
                break;
            case RequestState::startOfText:
                m_Message[m_ReceivedMessageLength] = byte;
                ++m_ReceivedMessageLength;
                m_Message[m_ReceivedMessageLength] = '\0';

                if (m_ReceivedMessageLength == m_MessageLength)
                {
                    m_RequestState = RequestState::textReceived;
                }
                break;
            case RequestState::textReceived:
                if (byte == ControlCharacters::etx)
                {
                    m_RequestState = RequestState::endOfText;
                }
                break;
            case RequestState::endOfText:
                if (byte == ControlCharacters::eot)
                {
                    m_RequestState = RequestState::null;
                }
                break;

        }
    }
}


void UARTInterruptMasterConnection::RequestData ()
{
    if (m_RequestState == RequestState::null)
    {
        m_InterruptPin.Enable();
        m_RequestState = RequestState::pending;
        m_MessageLength = 0;
        m_ReceivedMessageLength = 0;
        m_InterruptPin.Disable();
    }
}


bool UARTInterruptMasterConnection::ResponseReceived ()
{
    return (m_RequestState == RequestState::null);
}


const char* UARTInterruptMasterConnection::GetMessage ()
{
    return m_Message;
}


uint8_t UARTInterruptMasterConnection::GetMessageLength ()
{
    return m_MessageLength;
}
