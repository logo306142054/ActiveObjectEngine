
#include "stdafx.h"
#include "active_object_engine.h"
#include "func_command.h"
#include "sleep_command.h"
#include "delay_and_repeat.h"

class StopCommand : public DelayAndRepeat
{
public:
    virtual void Exectue()
    {
        m_engine.SetState(STOP);
        printf("stop\n");
    }
public:
    StopCommand(int delayTime, ActiveObjectEngine & engine) : DelayAndRepeat(delayTime, engine)
    {
        
    }
    ~StopCommand(){}
private:
};

class ExecOnce : public Command
{
public:
    ExecOnce(ActiveObjectEngine & engine) : m_engine(engine)
    {

    }
    
    // ͨ�� Command �̳�
    virtual void Exectue() override
    {
        printf("execute once\n");
    }
private:
    ActiveObjectEngine &m_engine;
};


int _tmain(int argc, _TCHAR* argv[])
{
    ActiveObjectEngine engine;
    FuncCommand f1('a', 0, 1, engine);
    FuncCommand f2('b', 3, 2, engine);
    FuncCommand f3('c', 4, 3, engine);
    FuncCommand f4('d', 1, 1, engine);
    StopCommand sc(12, engine);
    FuncCommand f5('e', 0, 5, engine);

    ExecOnce once(engine);
    SleepCommand s2(5, engine, once);
    engine.AddCommand(s2);

    engine.SetState(START);
    engine.Run();
    
    int _i = 0;
    //scanf("%d", &_i);
    return 0;
}
