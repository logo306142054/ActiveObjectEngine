//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif�����active_object_engine.h
#pragma once
#include "thread.h"
#include <windows.h>

class WinThreadCreator : public Thread
{
public:
    WinThreadCreator(IRunnable * pRunnable, char *taskName);

    virtual void Start();
    
private:
    static unsigned long ThreadRun(LPVOID pParam);
    void Run();
    void Finish();
public:
    virtual ~WinThreadCreator();

private:
    HANDLE m_handle;
};
