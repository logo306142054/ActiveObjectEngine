#include "../prih/window_thread_creator.h"
#include "runnable_if.h"
#include <process.h>
#include <windows.h>

/*
windows版本的线程创建差异类，这里只是为了测试而打桩，公司的项目是运行在linux下的
*/
void SleepToFreeCPU()
{
    ::Sleep(1);
}
Thread * CreateNewThread(IRunnable * pRunnable, char *pThreadName)
{
    return new WinThreadCreator(pRunnable, pThreadName);
}

unsigned long WinThreadCreator::ThreadRun(LPVOID pParam)
{
    WinThreadCreator & thread = *static_cast<WinThreadCreator*>(pParam);
    thread.Run();

    return 0;
}

WinThreadCreator::WinThreadCreator(IRunnable * pRunnable, char *taskName) 
    : Thread(pRunnable, taskName)
{
    
}

void WinThreadCreator::Start()
{
    if (m_hasStarted)
    {
        return;
    }
    m_hasStarted = true;
    m_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRun, (void*)this, 0, &m_dwTaskId);
}

void WinThreadCreator::Run()
{
    if (m_pRunnable != NULL)
    {
        m_pRunnable->Run();
        SleepToFreeCPU();//释放cpu，避免cpu一直被占用
    }
}

void WinThreadCreator::Finish()
{
    if (!m_hasStarted)
    {
        return;
    }
    if (m_pRunnable != NULL)
        m_pRunnable->Stop();
    CloseHandle(m_handle);
    m_pRunnable = NULL;
}

WinThreadCreator::~WinThreadCreator()
{
    Finish();
    SleepToFreeCPU();//等待线程停止
}
