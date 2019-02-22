//
// Created by Brendan Berg on 14.02.19.
//

#ifndef ATAR_CENTRAL_UARTCONFIG_HPP
#define ATAR_CENTRAL_UARTCONFIG_HPP

#include <stdint.h>


struct UARTProtocolConfig
{

    // frequencies

    uint32_t cpu_freq;

    uint32_t baud_rate;

    // frame format

    uint8_t frame_bits : 4;

    uint8_t parity_bit : 2;

    uint8_t stop_bits : 1;

    // double speed operation

    uint8_t double_speed_op : 1;

    // constants

    static constexpr uint8_t parity_null = 0;

    static constexpr uint8_t parity_odd = 1;

    static constexpr uint8_t parity_even = 2;

    static constexpr uint8_t stop_bit_single = 0;

    static constexpr uint8_t stop_bit_double = 1;


};


struct UARTRegisterConfig
{
    // registers

    uint8_t* udr;

    uint8_t* ucsr_a;

    uint8_t* ucsr_b;

    uint8_t* ucsr_c;

    uint8_t* ubrr_h;

    uint8_t* ubrr_l;
};


#endif //ATAR_CENTRAL_UARTCONFIG_HPP
