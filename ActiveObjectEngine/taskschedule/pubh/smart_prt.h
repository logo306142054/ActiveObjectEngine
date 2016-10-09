#pragma once

/*
实现智能指针，自动回收资源,请百度实现原理
*/
template <class PRT>
class SmartPrt
{
private:
    template <class T>
    class PrtCount
    {
    public:
        PrtCount(T * prt) : m_prt(prt), count(1) {}
        ~PrtCount()
        {
            if (m_prt != NULL)
            {
                //printf("count = 0, delete\n");
                delete m_prt;
                m_prt = NULL;
            }
        }
        T * m_prt;
        int count;
    };

public:
    SmartPrt(PRT * prt) : m_prtCount(new PrtCount<PRT>(prt))
    {

    }

    SmartPrt(const SmartPrt& prt) : m_prtCount(prt.m_prtCount)
    {
        ++prt.m_prtCount->count;
        //printf("c+1=%d\n", m_prtCount->count);
    }

    SmartPrt& operator = (const SmartPrt& prt)
    {
        if (this != &prt)
        {
            //printf("=operator rc=%d\n", prt.m_prtCount->count);
            ++prt.m_prtCount->count;
            if (--m_prtCount->count == 0)
                delete m_prtCount;

            m_prtCount = prt.m_prtCount;
        }
        return *this;
    }

    ~SmartPrt()
    {
        //printf("c-1=%d\n", m_prtCount->count - 1);
        if (m_prtCount != NULL)
        {
            if (--m_prtCount->count == 0)
                delete m_prtCount;
        }
    }

    PRT* operator ->()
    {
        return m_prtCount->m_prt;
    }
    PRT& operator *()
    {
        return *m_prtCount->m_prt;
    }
private:
    PrtCount<PRT> * m_prtCount;
};