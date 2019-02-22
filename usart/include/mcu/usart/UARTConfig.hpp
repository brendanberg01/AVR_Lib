//
// Created by Brendan Berg on 14.02.19.
//

#ifndef ATAR_CENTRAL_UARTCONFIG_HPP
#define ATAR_CENTRAL_UARTCONFIG_HPP

#include <stdint.h>
#include <avr/io.h>

#define UART_NUM 0


struct UARTProtocolConfig
{

    // frequencies

    uint32_t cpuFreq;

    uint32_t baudFreq;

    // frame format

    uint8_t characterSize : 3;

    static constexpr uint8_t characterSize5 = 0x0;

    static constexpr uint8_t characterSize6 = 0x1;

    static constexpr uint8_t characterSize7 = 0x2;

    static constexpr uint8_t characterSize8 = 0x3;

    static constexpr uint8_t characterSize9 = 0x7;

    uint8_t parityBit : 2;

    static constexpr uint8_t parityBitDisabled = 0x0;

    static constexpr uint8_t parityBitEven     = 0x2;

    static constexpr uint8_t parityBitOdd      = 0x3;

    uint8_t stopBits : 1;

    static constexpr uint8_t stopBits1 = 0x0;

    static constexpr uint8_t stopBits2 = 0x1;

    // double speed operation

    uint8_t doubleSpeedOp : 1;

    static constexpr uint8_t doubleSpeedOpEnabled  = 0x0;

    static constexpr uint8_t doubleSpeedOpDisabled = 0x1;


};


struct UARTRegisterConfig
{

    // registers

    volatile uint8_t* udr;

    volatile uint8_t* ucsra;

    volatile uint8_t* ucsrb;

    volatile uint8_t* ucsrc;

    volatile uint8_t* ubrrh;

    volatile uint8_t* ubrrl;


    explicit UARTRegisterConfig (uint8_t usartID)
    {
        switch (usartID)
        {
#ifdef UDR0
#undef UART_NUM
#define UART_NUM 1
            default:
            case 0:
                udr = &UDR0;
                ucsra = &UCSR0A;
                ucsrb = &UCSR0B;
                ucsrc = &UCSR0C;
                ubrrh = &UBRR0H;
                ubrrl = &UBRR0L;
                break;
#endif
#ifdef UDR1
#undef UART_NUM
#define UART_NUM 2
            case 1:
                udr = &UDR1;
                ucsra = &UCSR1A;
                ucsrb = &UCSR1B;
                ucsrc = &UCSR1C;
                ubrrh = &UBRR1H;
                ubrrl = &UBRR1L;
                break;
#endif
#ifdef UDR2
#undef UART_NUM
#define UART_NUM 3
            case 2:
                udr = &UDR2;
                ucsra = &UCSR2A;
                ucsrb = &UCSR2B;
                ucsrc = &UCSR2C;
                ubrrh = &UBRR2H;
                ubrrl = &UBRR2L;
                break;
#endif
#ifdef UDR3
#undef UART_NUM
#define UART_NUM 4
            case 3:
                udr = &UDR3;
                ucsra = &UCSR3A;
                ucsrb = &UCSR3B;
                ucsrc = &UCSR3C;
                ubrrh = &UBRR3H;
                ubrrl = &UBRR3L;
                break;
#endif
        }
    }


};


#endif //ATAR_CENTRAL_UARTCONFIG_HPP
