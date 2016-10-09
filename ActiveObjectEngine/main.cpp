
#include "stdafx.h"
#include "active_object_engine.h"
#include "sleep_command.h"
#include "message.h"
#include "thread.h"
#include "delay_and_repeat.h"

//��ʱ������
class StopCommand : public ICommand
{
public:
    virtual void Execute(CMessage * pMessage = NULL) override
    {
        printf("ʱ�䵽���Զ�ֹͣ����\n%s,%d\n", __FILE__, __LINE__);
        m_engine.Stop();
    }

    virtual const ostringstream & ToString() override
    {
        return m_oss;
    }

public:
    StopCommand(ActiveObjectEngine & engine) : m_engine(engine){}
    ~StopCommand(){}

private:
    ActiveObjectEngine &m_engine;
    ostringstream m_oss;
};

//�����Զ���������
class TestGc : public ICommand
{
public:
    virtual void Execute(CMessage *)
    {
        //printf("aaaa\n");
    }

    virtual const ostringstream & ToString() override
    {
        return m_oss;
    }

public:
    TestGc(ActiveObjectEngine& engine) : m_engine(engine){}
    ~TestGc()
    {
        printf("1s ���ͷ���Դ\n");
    }

private:
    ostringstream m_oss;
    ActiveObjectEngine &m_engine;
};

//�ظ�ִ�У�ÿִ��һ�ξ���m_engine�����һ��ICommandʵ��
class AddTestGc : public DelayAndRepeat
{
public:
    // ͨ�� ICommand �̳�
    virtual void Execute(CMessage * pMsg) override
    {
        printf("add garbage\n");
        m_engine.AddCommand(SmartCmd(new TestGc(m_engine)));

        //����˯�ߣ��ȴ��ٴ�ִ��
        Sleep(pMsg);
    }

    virtual const ostringstream & ToString() override
    {
        return m_oss;
    }

public:
    AddTestGc(BYTE sleepTime, ActiveObjectEngine& engine)
        : DelayAndRepeat(sleepTime, engine)
    {
        m_oss.str("add_test_gc");
    }
    ~AddTestGc()
    {
        printf("del gc\n");
    }
};


void test_auto_gc()
{
    //��������"����"
    ActiveObjectEngine *engine = new ActiveObjectEngine("engine");

    //����������ĵ�3s����ʼִ������ÿ1s�ظ�ִ��һ��
    engine->AddCommand(SmartCmd(new SleepCommand(3, *engine, SmartCmd(new AddTestGc(1, *engine)))));
    //��������10s��ֹͣ����
    engine->AddCommand(SmartCmd(new SleepCommand(10, *engine, SmartCmd(new StopCommand(*engine)))));

    //�����߳�
    Thread *pTc = CreateNewThread(engine, "test gc");
    //�����߳�
    pTc->Start();

    int _i;
    scanf("%d", &_i);

    delete pTc;
    delete engine;
}

int _tmain(int argc, _TCHAR* argv[])
{
    test_auto_gc();
    
    int _i = 0;
    scanf("%d", &_i);
    return 0;
}
