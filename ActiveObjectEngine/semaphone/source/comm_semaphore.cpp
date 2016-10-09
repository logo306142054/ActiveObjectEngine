#include "comm_semephore.h"
#include <Windows.h>
#include "stdio.h"

/*
����windows���ٽ���Դ��ʵ��ֻ����ʱ���׮���ڹ�˾����Ŀ��ʹ�õ����ź�����ʵ���̼߳�Ļ���
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
