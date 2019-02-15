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

    bool Push (uint8_t pushContent)
    {
        if (m_Head == m_Tail - 1)
        {
            return false;
        }

        m_Stack[m_Head] = pushContent;
        ++m_Head;
        m_Head %= N;

        return true;
    };

    void Pop ()
    {
        if (IsEmpty()){
            return;
        }

        ++m_Tail;
        m_Tail %= N;
    };

    uint8_t Read ()
    {
        return m_Stack[m_Tail];
    }

    bool IsEmpty ()
    {
        return m_Tail == m_Head;
    }


private:

    uint8_t m_Stack[N];

    int m_Tail = 0;

    int m_Head = 0;


};


#endif //AVR_LIB_BUFFER_HPP
