//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif�����active_object_engine.h
#pragma once
#include "command_if.h"
#include <time.h>
#include "smart_prt.h"


//ǰ����������ٶ�
class ActiveObjectEngine;

/*
SleepCommand����ʵ��Command�ġ�˯�ߡ���������ʱʱ�䵽��ʱ���ٴ�ִ��Command��
�����ʵ�����뵽ActiveObjectEngine�Ķ����к󣬻ᷴ���ı�ִ�У�����ʱʱ�䲻��ʱ��
����Լ��ٴμ��뵽�����У�ʱ�䵽���Ժ󣬻Ὣ�䱣���m_cmd��������У��ȴ�ִ��
*/
class SleepCommand : public ICommand
{

public:
    //����executeָ��
    virtual void Execute(CMessage *);

    //���ظ���ʵ�����ַ�����Ϣ�����ڶ�λ
    virtual const ostringstream & ToString() ;
    
private:
    inline bool IsContinueToSleep(time_t curTime);

public:
    SleepCommand(BYTE delayTime, ActiveObjectEngine & engine, SmartPrt<ICommand> cmd);
    ~SleepCommand();

private:
    ActiveObjectEngine & m_engine;
    SmartPrt<ICommand> m_cmd;
    BYTE m_sleepTime;
    time_t m_preTime;
    bool m_started;
    ostringstream m_oss;
};

