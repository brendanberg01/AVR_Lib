//
// Created by Passi on 15.02.2019.
//

#ifndef AVR_LIB_BUFFER_HPP
#define AVR_LIB_BUFFER_HPP

#include <stdint.h>


template<int N>
class Buffer
{
public:

    Buffer ()
        : m_Head(0), m_Tail(0)
    { }

    bool Push (uint8_t data)
    {
        if ((m_Head + 1) % N == m_Tail)
        {
            return false;
        }

        m_Stack[m_Head] = data;
        ++m_Head;
        m_Head %= N;

        return true;
    }

    void Pop ()
    {
        if (IsEmpty())
        {
            return;
        }

        ++m_Tail;
        m_Tail %= N;
    }

    uint8_t Read ()
    {
        return m_Stack[m_Tail];
    }

    bool IsEmpty ()
    {
        return m_Tail == m_Head;
    }


private:

    uint8_t m_Stack[N] = {0};

    int m_Head = 0;

    int m_Tail = 0;


};


#endif //AVR_LIB_BUFFER_HPP
