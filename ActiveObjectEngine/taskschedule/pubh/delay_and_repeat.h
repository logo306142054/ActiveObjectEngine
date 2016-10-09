//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif�����active_object_engine.h
#pragma once
#include "command_if.h"

class ActiveObjectEngine;
class SleepCommand;

/*
DelayAndRepeat����ʵ��Command���ظ�ִ�У�
�����ʵ�����뵽ActiveObjectEngine�Ķ����к󣬻�����ʱʱ�䵽���Ժ�õ�ִ�У�
����Ҫ�ٴν��롰˯�ߡ����ظ�ִ�У�ֻ�������ŵ�SleepCommand��ʵ���У����Ѹ�ʵ���ٴ�
���뵽������
*/
class DelayAndRepeat : public ICommand
{
public:
    //����executeָ��
    virtual void Execute(CMessage *pMessage = NULL) = 0;
    //���ظ���ʵ�����ַ�����Ϣ�����ڶ�λ
    virtual const ostringstream & ToString() = 0;

protected:
    /** �Թ��캯���д����sleep time��ʼ����sleep״̬*/
    void Sleep(CMessage *pMsg);
    /** �Ը�����sleep time��ʼ����sleep״̬*/
    void Sleep(BYTE newSleepTime, CMessage *pMsg);

public:
    DelayAndRepeat(BYTE sleepTime, ActiveObjectEngine& engine);

    virtual ~DelayAndRepeat();

protected:
    BYTE m_sleepTime;
    ActiveObjectEngine & m_engine;
    ostringstream m_oss;
};
