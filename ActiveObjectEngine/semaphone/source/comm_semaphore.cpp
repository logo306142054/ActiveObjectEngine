#include "comm_semephore.h"
#include <Windows.h>
#include "stdio.h"

/*
以下windows的临界资源的实现只是临时打个桩，在公司的项目中使用的是信号量来实现线程间的互斥
*/
CRITICAL_SECTION sections;
void CRtnSemaphore::Lock()
{
    EnterCriticalSection(&sections);
}

void CRtnSemaphore::UnLock()
{
    LeaveCriticalSection(&sections);
}

void CRtnSemaphore::RegMSem(char * pSemName, int flag)
{
    InitializeCriticalSection(&sections);
}

void CRtnSemaphore::UnRegSem()
{
    DeleteCriticalSection(&sections);
}

CRtnSemaphore::CRtnSemaphore()
{
}

CRtnSemaphore::~CRtnSemaphore()
{
    UnRegSem();
}
