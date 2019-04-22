//
// Created by Brendan Berg on 2019-04-22.
//

#ifndef ATAR_ALPHA_UARTINTERRUPTSLAVECONNECTION_HPP
#define ATAR_ALPHA_UARTINTERRUPTSLAVECONNECTION_HPP

#include <mcu/interrupt/ExternalInterruptHandler.hpp>

#include "UARTConnection.hpp"
#include "UARTDataSource.hpp"
#include "ControlCharacters.hpp"


class UARTInterruptSlaveConnection : public UARTConnection,
                                     public ExternalInterruptHandler
{
public:

    UARTInterruptSlaveConnection (uint8_t uartId, uint32_t baud,
                                  uint8_t extIntrptId,
                                  UARTDataSource& dataSource);

    void InterruptServiceRoutine () override;


private:

    UARTDataSource& m_DataSource;


};


#endif //ATAR_ALPHA_UARTINTERRUPTSLAVECONNECTION_HPP
