//
// Created by Brendan Berg on 2019-04-21.
//

#ifndef ATAR_CENTRAL_UARTINTERRUPTMASTERCONNECTION_HPP
#define ATAR_CENTRAL_UARTINTERRUPTMASTERCONNECTION_HPP

#include <mcu/io/DigitalOutputPin.hpp>

#include "ControlCharacters.hpp"
#include "UARTConnection.hpp"


class UARTInterruptMasterConnection : public UARTConnection
{
public:

    UARTInterruptMasterConnection (uint8_t uartID, uint32_t baud,
                                   volatile uint8_t* port, uint8_t bit);

    void Update ();

    void RequestData ();

    bool ResponseReceived ();

    const char* GetMessage();

    uint8_t GetMessageLength();


private:

    enum class RequestState
    {
        null,
        pending,
        startOfHeader,
        headerReceived,
        startOfText,
        textReceived,
        endOfText
    };

    DigitalOutputPin m_InterruptPin;

    char m_Message[64] = {'\0'};

    uint8_t m_MessageLength;

    uint8_t m_ReceivedMessageLength;

    RequestState m_RequestState;

};


#endif //ATAR_CENTRAL_UARTINTERRUPTMASTERCONNECTION_HPP
