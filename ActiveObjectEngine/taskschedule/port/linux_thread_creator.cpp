#include "../prih/linux_thread_creator.h"
#include "runnable_if.h"

/*
linux�汾���̴߳��������࣬����ֻ�ǿ�ʵ��
*/
void SleepToFreeCPU()
{

}
Thread * CreateNewThread(IRunnable * pRunnable, char *taskName)
{
    return new LinuxThreadCreator(pRunnable, taskName);
}


LinuxThreadCreator::LinuxThreadCreator(IRunnable * pRunnable, char *pThreadName) 
    : Thread(pRunnable, pThreadName)
{
    
}

void LinuxThreadCreator::Start()
{
    if (m_hasStarted)
    {
        return;
    }
    m_hasStarted = true;
    //TODO
}

void LinuxThreadCreator::Run()
{
    if (m_pRunnable != 0)
    {
        m_pRunnable->Run();
    }
}

void LinuxThreadCreator::Finish()
{
    if (!m_hasStarted)
    {
        return;
    }
    if (m_pRunnable != 0)
        m_pRunnable->Stop();
    m_pRunnable = 0;
    //TODO
}

LinuxThreadCreator::~LinuxThreadCreator()
{
    Finish();
    SleepToFreeCPU();//�ȴ��߳�ֹͣ
}
