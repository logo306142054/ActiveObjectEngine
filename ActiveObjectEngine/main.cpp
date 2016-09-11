
#include "stdafx.h"
#include "active_object_engine.h"
#include "func_command.h"
#include "sleep_command.h"

class StopCommand : public Command
{
public:
    virtual void Exectue()
    {
        m_engine.SetState(STOP);
        printf("stop\n");
    }
public:
    StopCommand(ActiveObjectEngine & engine) : m_engine(engine)
    {
        
    }
    ~StopCommand(){}
private:
    ActiveObjectEngine &m_engine;
};

int _tmain(int argc, _TCHAR* argv[])
{
    ActiveObjectEngine engine;
    
    //立即执行，每次间隔1s
    FuncCommand f1('a', 0, 1, engine);
    //延迟3s后执行，每次间隔2s
    FuncCommand f2('b', 3, 2, engine);
    //延迟4s后执行，每次间隔3s
    FuncCommand f3('c', 4, 3, engine);

    //10s之后停止
    StopCommand stop(engine);
    SleepCommand sc(10, engine, stop);
    engine.AddCommand(sc);

    engine.SetState(START);
    engine.Run();
    
    int _i = 0;
    //scanf("%d", &_i);
    return 0;
}
