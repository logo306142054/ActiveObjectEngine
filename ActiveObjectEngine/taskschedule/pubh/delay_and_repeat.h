//未避免头文件的重复包含，所有头文件都必须用#pragma once或者宏定义包含起来
//较老的gcc版本可能不支持#pragma，使用宏定义包含能起到同样的效果，就是麻烦一些
//在文件末尾记得不要漏了#endif，详见active_object_engine.h
#pragma once
#include "command_if.h"

class ActiveObjectEngine;
class SleepCommand;

/*
DelayAndRepeat用于实现Command的重复执行，
该类的实例加入到ActiveObjectEngine的队列中后，会在延时时间到了以后得到执行，
如需要再次进入“睡眠”并重复执行，只需把自身放到SleepCommand类实例中，并把该实例再次
加入到队列中
*/
class DelayAndRepeat : public ICommand
{
public:
    //接收execute指令
    virtual void Execute(CMessage *pMessage = NULL) = 0;
    //返回该类实例的字符串信息，用于定位
    virtual const ostringstream & ToString() = 0;

protected:
    /** 以构造函数中传入的sleep time开始进入sleep状态*/
    void Sleep(CMessage *pMsg);
    /** 以给定的sleep time开始进入sleep状态*/
    void Sleep(BYTE newSleepTime, CMessage *pMsg);

public:
    DelayAndRepeat(BYTE sleepTime, ActiveObjectEngine& engine);

    virtual ~DelayAndRepeat();

protected:
    BYTE m_sleepTime;
    ActiveObjectEngine & m_engine;
    ostringstream m_oss;
};
