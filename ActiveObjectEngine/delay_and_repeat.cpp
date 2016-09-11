#include "delay_and_repeat.h"
#include "sleep_command.h"
#include "active_object_engine.h"

/** 以构造函数中传入的sleep time开始进入sleep状态*/
void DelayAndRepeat::Sleep()
{
    Sleep(m_sleepTime);
}

/** 以给定的sleep time开始进入sleep状态*/
void DelayAndRepeat::Sleep(BYTE newSleepTime)
{
    if (m_sleepOwn != nullptr)
    {
        m_sleepOwn->SetSleepTime(newSleepTime);
        AddToEngine();
    }
}

void DelayAndRepeat::AddToEngine()
{
    m_engine.AddCommand(*(dynamic_cast<Command*>(m_sleepOwn)));
}

/**是否延迟指定时间之后再执行命令：m_delayTime<=0表示不延迟,直接开始*/
bool DelayAndRepeat::IsExecWithoutDelay()
{
    return m_delayTime <= 0;
}

/*delayTime 延迟指定时间之后才开始执行
  sleepTime 每次执行之后进入sleep状态的时间，即每两次执行间隔的时间
  */
DelayAndRepeat::DelayAndRepeat(BYTE delayTime, BYTE sleepTime, ActiveObjectEngine& engine)
    : m_delayTime(delayTime),
    m_sleepTime(sleepTime),
    m_engine(engine)
{
    if (IsExecWithoutDelay())
    {
        m_sleepOwn = new SleepCommand(sleepTime, m_engine, *this);
    }
    else
    {
        m_sleepOwn = new SleepCommand(delayTime, m_engine, *this);
    }
    
    AddToEngine();
}

DelayAndRepeat::DelayAndRepeat(BYTE sleepTime, ActiveObjectEngine& engine)
    : DelayAndRepeat(0, sleepTime, engine)
{

}

DelayAndRepeat::~DelayAndRepeat()
{
    if (m_sleepOwn != NULL) {
        delete m_sleepOwn;
        m_sleepOwn = NULL;
    }
}