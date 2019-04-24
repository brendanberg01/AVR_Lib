//
// Created by Brendan Berg on 2019-04-22.
//

#ifndef ATAR_ALPHA_UARTDATASOURCE_HPP
#define ATAR_ALPHA_UARTDATASOURCE_HPP

#include <stdint.h>


class UARTDataSource
{
public:

    const unsigned char* GetMessage ();

    uint8_t GetMessageLength ();


protected:

    explicit UARTDataSource (uint8_t messageLength);

    virtual void UpdateMessage () = 0;

    unsigned char m_Message[64] = {'\0'};

    uint8_t m_MessageLength;


};


#endif //ATAR_ALPHA_UARTDATASOURCE_HPP
