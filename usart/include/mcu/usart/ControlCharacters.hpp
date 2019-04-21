//
// Created by Brendan Berg on 2019-04-21.
//

#ifndef ATAR_CENTRAL_CONTROLCHARACTERS_HPP
#define ATAR_CENTRAL_CONTROLCHARACTERS_HPP


struct ControlCharacters
{
    static constexpr char nul = 0x00;
    static constexpr char soh = 0x01;
    static constexpr char stx = 0x02;
    static constexpr char etx = 0x03;
    static constexpr char eot = 0x04;
    static constexpr char enq = 0x05;
    static constexpr char ack = 0x06;
    static constexpr char bel = 0x07;
    static constexpr char bs = 0x08;
    static constexpr char ht = 0x09;
    static constexpr char lf = 0x0a;
    static constexpr char vt = 0x0b;
    static constexpr char ff = 0x0c;
    static constexpr char cr = 0x0d;
    static constexpr char so = 0x0e;
    static constexpr char si = 0x0f;
    static constexpr char dle = 0x10;
    static constexpr char dc1 = 0x11;
    static constexpr char dc2 = 0x12;
    static constexpr char dc3 = 0x13;
    static constexpr char dc4 = 0x14;
    static constexpr char nak = 0x15;
    static constexpr char syn = 0x16;
    static constexpr char etb = 0x17;
    static constexpr char can = 0x18;
    static constexpr char em = 0x19;
    static constexpr char sub = 0x1a;
    static constexpr char esc = 0x1b;
    static constexpr char fs = 0x1c;
    static constexpr char gs = 0x1d;
    static constexpr char rs = 0x1e;
    static constexpr char us = 0x1f;
    static constexpr char del = 0x7f;
};


#endif //ATAR_CENTRAL_CONTROLCHARACTERS_HPP
