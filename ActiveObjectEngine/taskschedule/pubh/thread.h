#pragma once

class IRunnable;

/*
�����µ��̣߳��߳����������й��캯���д����IRunnableʵ����
����������������
�´������̲߳�������ִ�У������start()����������
����������������
Ϊ����Ӧ�ó������𽥸��ӵ��µĲ���ȫ���⣬һ���߳��������������ⲿ
����ֹͣ������ֹͣ���뽫��ǰThread�������������´�����
����������������
��Thread��������ʱ�������IRunnableʵ����Stop(��������
��ȷ��������֮ǰ��IRunnableʵ���������ɷ��ʵġ�
*/
class Thread
{
public:
    virtual void Start() = 0;
public:
    Thread(IRunnable * pRunnable, char *pThreadName)
    {
        m_hasStarted = false;
        m_dwTaskId = 0;
        m_pRunnable = pRunnable;
        m_pThreadName = pThreadName;
    }

    virtual ~Thread() {}

protected:
    bool m_hasStarted;
    IRunnable * m_pRunnable;
    unsigned long m_dwTaskId;
    char * m_pThreadName;
};

extern Thread * CreateNewThread(IRunnable * pRunnable, char *pThreadName);