#include "active_object_engine.h"
#include "command.h"


void ActiveObjectEngine::AddCommand(Command & pCmd)
{
    cmds.push_back(&pCmd);
}

void ActiveObjectEngine::Run()
{
    while (!isStop())
    {
        if (isPause())
            continue;

        Command* cmd = cmds.front();
        if (cmd != NULL)
        { 
            cmd->Exectue();
        }
        cmds.pop_front();
    }
}


void ActiveObjectEngine::SetState(E_STATE state)
{
    m_state = state;
}

bool ActiveObjectEngine::isStop()
{
    return m_state == STOP;
}

bool ActiveObjectEngine::isPause()
{
    return m_state == PAUSE;
}

ActiveObjectEngine::ActiveObjectEngine()
{
    m_state = PAUSE;
}

ActiveObjectEngine::~ActiveObjectEngine()
{
    cmds.clear();
}