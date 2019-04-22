//
// Created by Brendan Berg on 2019-04-22.
//

#include <string.h>

#include <mcu/usart/UARTDataSource.hpp>


UARTDataSource::UARTDataSource (uint8_t messageLength)
    : m_MessageLength(messageLength)
{ }


const char* UARTDataSource::GetMessage ()
{
    UpdateMessage();
    m_Message[m_MessageLength] = '\0';
    return m_Message;
}


uint8_t UARTDataSource::GetMessageLength ()
{
    return m_MessageLength;
}
