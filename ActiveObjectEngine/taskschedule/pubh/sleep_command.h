//未避免头文件的重复包含，所有头文件都必须用#pragma once或者宏定义包含起来
//较老的gcc版本可能不支持#pragma，使用宏定义包含能起到同样的效果，就是麻烦一些
//在文件末尾记得不要漏了#endif，详见active_object_engine.h
#pragma once
#include "command_if.h"
#include <time.h>
#include "smart_prt.h"


//前置声明，请百度
class ActiveObjectEngine;

/*
SleepCommand用于实现Command的“睡眠”，并在延时时间到达时，再次执行Command。
该类的实例加入到ActiveObjectEngine的队列中后，会反复的被执行，当延时时间不到时，
会把自己再次加入到队列中，时间到了以后，会将其保存的m_cmd加入队列中，等待执行
*/
class SleepCommand : public ICommand
{

public:
    //接收execute指令
    virtual void Execute(CMessage *);

    //返回该类实例的字符串信息，用于定位
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

