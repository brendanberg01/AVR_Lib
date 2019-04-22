//
// Created by Brendan Berg on 19.04.19.
//

#ifndef ATAR_CENTRAL_TIMERCONFIG_HPP
#define ATAR_CENTRAL_TIMERCONFIG_HPP

#include <stdint.h>
#include <avr/io.h>


struct TimerModeConfig
{

    // waveform generation

    uint8_t waveform : 4;

    static constexpr uint8_t waveform8Normal      = 0x0;
    static constexpr uint8_t waveform8PwmPcMax    = 0x1;
    static constexpr uint8_t waveform8Ctc         = 0x2;
    static constexpr uint8_t waveform8PwmFastMax  = 0x3;
    static constexpr uint8_t waveform8PwmPcOcra   = 0x5;
    static constexpr uint8_t waveform8PwmFastOcra = 0x7;

    static constexpr uint8_t waveform16Normal       = 0x0;
    static constexpr uint8_t waveform16PwmPc8bit    = 0x1;
    static constexpr uint8_t waveform16PwmPc9bit    = 0x2;
    static constexpr uint8_t waveform16PwmPc10bit   = 0x3;
    static constexpr uint8_t waveform16Ctc          = 0x4;
    static constexpr uint8_t waveform16PwmFast8bit  = 0x5;
    static constexpr uint8_t waveform16PwmFast9bit  = 0x6;
    static constexpr uint8_t waveform16PwmFast10bit = 0x7;
    static constexpr uint8_t waveform16PwmPcOcra    = 0xb;
    static constexpr uint8_t waveform16PwmFastOcra  = 0xf;

    // clock source

    uint8_t clockSource : 3;

    static constexpr uint8_t clockSourceNon        = 0x0;
    static constexpr uint8_t clockSourcePs1        = 0x1;
    static constexpr uint8_t clockSourcePs8        = 0x2;
    static constexpr uint8_t clockSourcePs64       = 0x3;
    static constexpr uint8_t clockSourcePs256      = 0x4;
    static constexpr uint8_t clockSourcePs1024     = 0x5;
    static constexpr uint8_t clockSourceExtFalling = 0x6;
    static constexpr uint8_t clockSourceExtRising  = 0x7;


};


struct TimerRegisterConfig
{

    // type

    bool twoBytes;

    // registers

    volatile uint8_t* tccra;

    volatile uint8_t* tccrb;

    volatile uint8_t* ocra;

    volatile uint8_t* ocrb;

    volatile uint8_t* ocrc;


    explicit TimerRegisterConfig (uint8_t timerID)
    {
#if defined(__AVR_ATmega328P__)
        switch (timerID)
        {
            default:
            case 0:
                twoBytes = false;
                tccra = &TCCR0A;
                tccrb = &TCCR0B;
                ocra = &OCR0A;
                ocrb = &OCR0B;
                ocrc = nullptr;
                break;
            case 1:
                twoBytes = true;
                tccra = &TCCR1A;
                tccrb = &TCCR1B;
                ocra = &OCR1AL;
                ocrb = &OCR1BL;
                ocrc = nullptr;
                break;
            case 2:
                twoBytes = false;
                tccra = &TCCR2A;
                tccrb = &TCCR2B;
                ocra = &OCR2A;
                ocrb = &OCR2B;
                ocrc = nullptr;
                break;
        }
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
        switch (timerID)
        {
            default:
            case 0:
                twoBytes = false;
                tccra = &TCCR0A;
                tccrb = &TCCR0B;
                ocra = &OCR0A;
                ocrb = &OCR0B;
                ocrc = nullptr;
                break;
            case 1:
                twoBytes = true;
                tccra = &TCCR1A;
                tccrb = &TCCR1B;
                ocra = &OCR1AL;
                ocrb = &OCR1BL;
                ocrc = &OCR1CL;
                break;
            case 2:
                twoBytes = false;
                tccra = &TCCR2A;
                tccrb = &TCCR2B;
                ocra = &OCR2A;
                ocrb = &OCR2B;
                ocrc = nullptr;
                break;
            case 3:
                twoBytes = true;
                tccra = &TCCR3A;
                tccrb = &TCCR3B;
                ocra = &OCR3AL;
                ocrb = &OCR3BL;
                ocrc = &OCR3CL;
                break;
            case 4:
                twoBytes = true;
                tccra = &TCCR4A;
                tccrb = &TCCR4B;
                ocra = &OCR4AL;
                ocrb = &OCR4BL;
                ocrc = &OCR4CL;
                break;
            case 5:
                twoBytes = true;
                tccra = &TCCR5A;
                tccrb = &TCCR5B;
                ocra = &OCR5AL;
                ocrb = &OCR5BL;
                ocrc = &OCR5CL;
                break;
        }
#endif
    }


};


struct TimerCompareMatchConfig
{

    // output compare register

    uint8_t outputCompareRegister;

#if defined(__AVR_ATmega328P__)
    static constexpr uint8_t outputCompareRegisterBits[2] =
        {COM0A0, COM0B0};
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
    static constexpr uint8_t outputCompareRegisterBits[3] =
        {COM0A0, COM0B0, COM1C0};
#endif

    // compare match

    uint8_t compareMatchMode : 2;

    static constexpr uint8_t compareMatchModeNormal  = 0x0;
    static constexpr uint8_t compareMatchModeToggle  = 0x1;
    static constexpr uint8_t compareMatchModeDisable = 0x2;
    static constexpr uint8_t compareMatchModeEnable  = 0x3;


    TimerCompareMatchConfig (uint8_t ocr, uint8_t mode)
        : compareMatchMode(mode)
    {
#if defined(__AVR_ATmega328P__)
        switch (ocr)
        {
            default:
            case 0:
                outputCompareRegister = COM0A0;
                break;
            case 1:
                outputCompareRegister = COM0B0;
                break;
        }
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
        switch (ocr)
        {
            default:
            case 0:
                outputCompareRegister = COM0A0;
                break;
            case 1:
                outputCompareRegister = COM0B0;
                break;
            case 2:
                outputCompareRegister = COM1C0;
                break;
        }
#endif
    }


};


#endif //ATAR_CENTRAL_TIMERCONFIG_HPP
