//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif�����active_object_engine.h
#pragma once
#include "thread.h"


class LinuxThreadCreator : public Thread
{
public:
    LinuxThreadCreator(IRunnable * pRunnable, char *taskName);
    virtual void Start();
private:
    void Run();
    void Finish();
public:
    virtual ~LinuxThreadCreator();
};