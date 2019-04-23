//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_CENTRAL_UARTDATADESTINATION_HPP
#define ATAR_CENTRAL_UARTDATADESTINATION_HPP

#include <stdint.h>


class UARTDataDestination
{
public:

    virtual void DispatchMessage (const char* message, uint8_t len) = 0;


};


#endif //ATAR_CENTRAL_UARTDATADESTINATION_HPP
