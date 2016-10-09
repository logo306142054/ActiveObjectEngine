#include "define.h"
#include "delay_and_repeat.h"
#include "sleep_command.h"
#include "active_object_engine.h"
#include "message.h"
/** �Թ��캯���д����sleep time��ʼ����sleep״̬*/
void DelayAndRepeat::Sleep(CMessage *pMsg)
{
    Sleep(m_sleepTime, pMsg);
}

/** �Ը�����sleep time��ʼ����sleep״̬*/
void DelayAndRepeat::Sleep(BYTE newSleepTime, CMessage *pMsg)
{
    SmartCmd newCmd(*static_cast<SmartCmd*>(pMsg->m_pMessageData));
    m_engine.AddCommand(SmartCmd(new SleepCommand(newSleepTime, m_engine, newCmd)));
}

DelayAndRepeat::DelayAndRepeat(BYTE sleepTime, ActiveObjectEngine& engine)
    : m_sleepTime(sleepTime), m_engine(engine)
{

}

DelayAndRepeat::~DelayAndRepeat()
{
}