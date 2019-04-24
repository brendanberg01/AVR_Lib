//
// Created by Brendan Berg on 14.02.19.
//

#include <mcu/usart/UARTConnection.hpp>


UARTConnection* UARTConnection::instancePtr[UART_NUM] = {nullptr};


UARTConnection::UARTConnection (uint8_t uartID, uint32_t baud,
                                UARTDataDestination& destination)
    : m_OngoingTransmission(false), m_RequestState(RequestState::pending),
    m_MessageLength(0), m_ReceivedMessageLength(0),
    m_DataDestination(destination)
{
    UARTProtocolConfig uartPrtclCfg = {};
    uartPrtclCfg.cpuFreq       = 16000000;
    uartPrtclCfg.baudFreq      = baud;
    uartPrtclCfg.characterSize = UARTProtocolConfig::characterSize8;
    uartPrtclCfg.parityBit     = UARTProtocolConfig::parityBitOdd;
    uartPrtclCfg.stopBits      = UARTProtocolConfig::stopBits1;
    uartPrtclCfg.doubleSpeedOp = UARTProtocolConfig::doubleSpeedOpDisabled;

    m_UART = UART(uartPrtclCfg, uartID);

    m_UART.EnableReceiveCompleteInterrupt();
    m_UART.EnableTransmitCompleteInterrupt();

    UARTConnection::instancePtr[uartID] = this;
}


bool UARTConnection::DataAvailable ()
{
    return !m_ReceiveBuffer.IsEmpty();
}


uint8_t UARTConnection::ReadByte ()
{
    auto data = m_ReceiveBuffer.Read();
    m_ReceiveBuffer.Pop();
    return data;
}


void UARTConnection::WriteByte (uint8_t data)
{
    m_TransmitBuffer.Push(data);
    if (!m_OngoingTransmission)
    {
        m_OngoingTransmission = true;
        StartTransmission();
    }
}


void UARTConnection::WriteString (const unsigned char data[])
{
    auto len = strlen(reinterpret_cast<const char*>(data));
    WriteString(data, len);
}


void UARTConnection::WriteString (const unsigned char data[], uint8_t len)
{
    for (int i = 0; i < len; ++i)
    {
        WriteByte(static_cast<uint8_t>(data[i]));
    }
}


void UARTConnection::SendData (UARTDataSource& dataSource)
{
    WriteByte(ControlCharacters::soh);
    WriteByte(dataSource.GetMessageLength());
    WriteByte(ControlCharacters::stx);
    WriteString(dataSource.GetMessage(), dataSource.GetMessageLength());
    WriteByte(ControlCharacters::etx);
    WriteByte(ControlCharacters::eot);
}


void UARTConnection::ReceiveData ()
{
    if (m_RequestState == RequestState::null)
    {
        return;
    }

    while (DataAvailable())
    {
        uint8_t byte = ReadByte();

        switch (m_RequestState)
        {
            case RequestState::null:
            case RequestState::pending:
                if (byte == ControlCharacters::soh)
                {
                    m_RequestState = RequestState::startOfHeader;
                }
                break;
            case RequestState::startOfHeader:
                m_MessageLength = byte;
                m_RequestState = RequestState::headerReceived;
                break;
            case RequestState::headerReceived:
                if (byte == ControlCharacters::stx)
                {
                    m_RequestState = RequestState::startOfText;
                }
                break;
            case RequestState::startOfText:
                m_Message[m_ReceivedMessageLength] = byte;
                ++m_ReceivedMessageLength;
                m_Message[m_ReceivedMessageLength] = '\0';

                if (m_ReceivedMessageLength == m_MessageLength)
                {
                    m_RequestState = RequestState::textReceived;
                }
                break;
            case RequestState::textReceived:
                if (byte == ControlCharacters::etx)
                {
                    m_RequestState = RequestState::endOfText;
                }
                break;
            case RequestState::endOfText:
                if (byte == ControlCharacters::eot)
                {
                    m_RequestState = RequestState::null;
                    DispatchMessage();
                }
                break;

        }
    }
}


bool UARTConnection::MessageReceived ()
{
    return ((m_RequestState == RequestState::null) && (m_MessageLength != 0));
}


uint8_t UARTConnection::GetMessageLength ()
{
    return m_MessageLength;
}


const unsigned char* UARTConnection::GetMessage ()
{
    return m_Message;
}


void UARTConnection::DispatchMessage ()
{
    m_DataDestination.DispatchMessage(GetMessage(), GetMessageLength());
    DiscardMessage();
}


void UARTConnection::DiscardMessage ()
{
    if (MessageReceived())
    {
        m_RequestState = RequestState::pending;
        m_Message[0] = '\0';
        m_MessageLength = 0;
        m_ReceivedMessageLength = 0;
    }
}


void UARTConnection::StartTransmission ()
{
    TransmitCompleteInterruptServiceRoutine();
}


void UARTConnection::ReceiveCompleteInterruptServiceRoutine ()
{
    auto data = static_cast<uint8_t>(m_UART.Receive());
    m_ReceiveBuffer.Push(data);
}


void UARTConnection::TransmitCompleteInterruptServiceRoutine ()
{
    if (m_TransmitBuffer.IsEmpty())
    {
        m_OngoingTransmission = false;
        return;
    }

    if (!m_UART.DataRegisterEmpty())
    {
        return;
    }

    auto data = m_TransmitBuffer.Read();
    m_TransmitBuffer.Pop();
    m_UART.Transmit(data);
}


#define RCISR(vect, i) ISR (vect)\
{\
    UARTConnection::instancePtr[i]->ReceiveCompleteInterruptServiceRoutine();\
}

#define TCISR(vect, i) ISR (vect)\
{\
    UARTConnection::instancePtr[i]->TransmitCompleteInterruptServiceRoutine();\
}

#if defined(__AVR_ATmega328P__)
RCISR(USART_RX_vect, 0)
TCISR(USART_TX_vect, 0)
#endif

#if defined(__AVR__ATmega1280__) || defined(__AVR_ATmega2560__)
RCISR(USART0_RX_vect, 0)
TCISR(USART0_TX_vect, 0)
RCISR(USART1_RX_vect, 1)
TCISR(USART1_TX_vect, 1)
RCISR(USART2_RX_vect, 2)
TCISR(USART2_TX_vect, 2)
RCISR(USART3_RX_vect, 3)
TCISR(USART3_TX_vect, 3)
#endif
