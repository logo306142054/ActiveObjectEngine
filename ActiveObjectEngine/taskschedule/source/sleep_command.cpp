#include "define.h"
#include "sleep_command.h"
#include "active_object_engine.h"
#include "message.h"

void SleepCommand::Execute(CMessage * pMsg)
{
    time_t curTime;
    time(&curTime);

    if (!m_started)
    {
        m_started = true;
        m_preTime = curTime;
        m_engine.AddCommand(*static_cast<SmartCmd*>(pMsg->m_pMessageData));
    }
    else if (IsContinueToSleep(curTime))
    {   
        m_engine.AddCommand(*static_cast<SmartCmd*>(pMsg->m_pMessageData));
    }
    else
    {
        m_engine.AddCommand(m_cmd);
    }
}

bool SleepCommand::IsContinueToSleep(time_t curTime)
{
    return difftime(curTime, m_preTime) < m_sleepTime;
}

const ostringstream & SleepCommand::ToString()
{
    return m_oss;
}

SleepCommand::SleepCommand(BYTE sleepTime, ActiveObjectEngine & engine, SmartPrt<ICommand> cmd)
    :m_sleepTime(sleepTime),
    m_engine(engine),
    m_cmd(cmd)
{
    m_started = false;
    m_oss.str("sleep command");
}


SleepCommand::~SleepCommand()
{
}
