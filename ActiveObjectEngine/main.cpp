
#include "stdafx.h"
#include "active_object_engine.h"
#include "sleep_command.h"
#include "message.h"
#include "thread.h"
#include "delay_and_repeat.h"

//临时测试用
class StopCommand : public ICommand
{
public:
    virtual void Execute(CMessage * pMessage = NULL) override
    {
        printf("时间到，自动停止任务\n%s,%d\n", __FILE__, __LINE__);
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

//测试自动垃圾回收
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
        printf("1s 后释放资源\n");
    }

private:
    ostringstream m_oss;
    ActiveObjectEngine &m_engine;
};

//重复执行，每执行一次就向m_engine中添加一个ICommand实例
class AddTestGc : public DelayAndRepeat
{
public:
    // 通过 ICommand 继承
    virtual void Execute(CMessage * pMsg) override
    {
        printf("add garbage\n");
        m_engine.AddCommand(SmartCmd(new TestGc(m_engine)));

        //进入睡眠，等待再次执行
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
    //创建任务"引擎"
    ActiveObjectEngine *engine = new ActiveObjectEngine("engine");

    //程序启动后的第3s，开始执行任务，每1s重复执行一次
    engine->AddCommand(SmartCmd(new SleepCommand(3, *engine, SmartCmd(new AddTestGc(1, *engine)))));
    //程序启动10s后停止任务
    engine->AddCommand(SmartCmd(new SleepCommand(10, *engine, SmartCmd(new StopCommand(*engine)))));

    //创建线程
    Thread *pTc = CreateNewThread(engine, "test gc");
    //启动线程
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
