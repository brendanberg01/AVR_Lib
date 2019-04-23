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
                                   UARTDataDestination& destination,
                                   volatile uint8_t* port, uint8_t bit);

    void RequestData ();

    bool ResponseReceived ();

    void DispatchMessage () override;

    void DiscardResponse ();


private:

    DigitalOutputPin m_InterruptPin;


};


#endif //ATAR_CENTRAL_UARTINTERRUPTMASTERCONNECTION_HPP
