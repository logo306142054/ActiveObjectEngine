#include "delay_and_repeat.h"
#include "sleep_command.h"
#include "active_object_engine.h"

/** �Թ��캯���д����sleep time��ʼ����sleep״̬*/
void DelayAndRepeat::Sleep()
{
    Sleep(m_sleepTime);
}

/** �Ը�����sleep time��ʼ����sleep״̬*/
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

/**�Ƿ��ӳ�ָ��ʱ��֮����ִ�����m_delayTime<=0��ʾ���ӳ�,ֱ�ӿ�ʼ*/
bool DelayAndRepeat::IsExecWithoutDelay()
{
    return m_delayTime <= 0;
}

/*delayTime �ӳ�ָ��ʱ��֮��ſ�ʼִ��
  sleepTime ÿ��ִ��֮�����sleep״̬��ʱ�䣬��ÿ����ִ�м����ʱ��
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