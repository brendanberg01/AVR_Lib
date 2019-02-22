//
// Created by Brendan Berg on 14.02.19.
//

#ifndef ATAR_CENTRAL_UARTCONNECTION_HPP
#define ATAR_CENTRAL_UARTCONNECTION_HPP

#include <stdint.h>
#include <string.h>
#include <avr/interrupt.h>

#include <mcu/util/Buffer.hpp>

#include "UART.hpp"


#ifdef UDR0
extern "C" void USART0_RX_vect(void) __attribute__ ((signal));
extern "C" void USART0_TX_vect(void) __attribute__ ((signal));
#endif

#ifdef UDR1
extern "C" void USART1_RX_vect(void) __attribute__ ((signal));
extern "C" void USART1_TX_vect(void) __attribute__ ((signal));
#endif

#ifdef UDR2
extern "C" void USART2_RX_vect(void) __attribute__ ((signal));
extern "C" void USART2_TX_vect(void) __attribute__ ((signal));
#endif

#ifdef UDR3
extern "C" void USART3_RX_vect(void) __attribute__ ((signal));
extern "C" void USART3_TX_vect(void) __attribute__ ((signal));
#endif


class UARTConnection
{

public:

    UARTConnection (uint8_t uartID, uint32_t baud);

    bool DataAvailable ();

    uint8_t ReadByte ();

    void WriteByte (uint8_t data);

    void WriteString (const char data[]);


private:

    UART m_UART;

    Buffer<128> m_TransmitBuffer;

    Buffer<128> m_ReceiveBuffer;

    bool m_OngoingTransmission;

    static UARTConnection* instancePtr[UART_NUM];

    void StartTransmission ();

    void ReceiveCompleteInterruptServiceRoutine ();

    void TransmitCompleteInterruptServiceRoutine ();


#ifdef UDR0
    friend void USART0_RX_vect();
    friend void USART0_TX_vect();
#endif

#ifdef UDR1
    friend void USART1_RX_vect();
    friend void USART1_TX_vect();
#endif

#ifdef UDR2
    friend void USART2_RX_vect();
    friend void USART2_TX_vect();
#endif

#ifdef UDR3
    friend void USART3_RX_vect();
    friend void USART3_TX_vect();
#endif


};


#endif //ATAR_CENTRAL_UARTCONNECTION_HPP
