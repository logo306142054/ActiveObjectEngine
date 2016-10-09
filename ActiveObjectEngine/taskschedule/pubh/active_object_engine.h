//未避免头文件的重复包含，所有头文件都必须用#pragma once或者宏定义包含起来
//较老的gcc版本可能不支持#pragma，使用宏定义包含能起到同样的效果，就是麻烦一些
//在文件末尾记得不要漏了#endif
#ifndef _ACTIVEE_OBJECT_ENGINE_H_
#define _ACTIVEE_OBJECT_ENGINE_H_

#include "runnable_if.h"
#include <list>
#include "command_if.h"
#include "smart_prt.h"

class CRtnSemaphore;

#define SmartCmd SmartPrt<ICommand>

class ActiveObjectEngine : public IRunnable {

public:
    virtual void Run();

    virtual void Stop();

    void AddCommand(SmartCmd& cmd);

protected:
    inline bool HasCmdToExec();

public:
    /*任务“引擎”的创建总是伴随着新线程的创建，而创建新线程时必须指定
     *唯一的任务名，将此任务名传入构造函数即可*/
    ActiveObjectEngine(char *pThreadName);
    virtual ~ActiveObjectEngine();

private:
    //list的实现原理是指针队列，当队列中的元素需要频繁增删时，用list的增删效率更高，但查找效率较低
    //vector的实现原理是数组，当队列中的元素不需要频繁增删时，用vector的查找效率更高，但是增删效率较低
    std::list<SmartCmd> m_cmds;
    CRtnSemaphore * m_sem;
    bool m_running;
};

#endif