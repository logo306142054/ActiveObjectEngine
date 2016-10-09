#include "active_object_engine.h"
#include "comm_type_def.h"
#include "comm_semephore.h"
#include "stdio.h"
#include "define.h"
#include "sleep_command.h"
#include "message.h"

extern void SleepToFreeCPU();

//��������ʱ����
const int GC_INTERVAL_TIME = 1;
//ϵͳ�������ӳ�5S���ٽ�����������
const int GC_DELAY_TIME = 1;

void ActiveObjectEngine::AddCommand(SmartCmd& cmd)
{
    RTN_AUTO_LOCK(m_sem);
    m_cmds.push_back(cmd);
}

/*
��ѭ�������������棬�˺������������߳��е���
*/
void ActiveObjectEngine::Run()
{
    m_running = true;
    while (m_running)
    {
        if (HasCmdToExec())
        {
            RTN_AUTO_LOCK(m_sem);
            SmartCmd& cmd = m_cmds.front();
            CMessage msg;
            msg.m_pMessageData = &cmd;
            cmd->Execute(&msg);
            //(*cmd).Execute(&msg);
            m_cmds.pop_front();
            RTN_AUTO_UNLOCK(m_sem);
        }
    }
}

void ActiveObjectEngine::Stop()
{
    m_running = false;
}

bool ActiveObjectEngine::HasCmdToExec()
{
    return !m_cmds.empty();
}

ActiveObjectEngine::ActiveObjectEngine(char *pThreadName)
{
    m_running = false;
    m_sem = new CRtnSemaphore();
    m_sem->RegMSem(pThreadName, 1);
}

ActiveObjectEngine::~ActiveObjectEngine()
{
    m_running = false;
    m_cmds.clear();
    DELETE_OBJECT(m_sem);
}
