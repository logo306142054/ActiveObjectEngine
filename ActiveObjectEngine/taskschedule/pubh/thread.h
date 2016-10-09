#pragma once

class IRunnable;

/*
创建新的线程，线程启动后将运行构造函数中传入的IRunnable实例。
————————
新创建的线程不会立即执行，需调用start()函数启动。
————————
为避免应用场景的逐渐复杂导致的不安全问题，一旦线程启动即不可由外部
调用停止。如需停止必须将当前Thread对象析构并重新创建。
————————
当Thread对象析构时，会调用IRunnable实例的Stop(）函数，
请确保在析构之前，IRunnable实例是正常可访问的。
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