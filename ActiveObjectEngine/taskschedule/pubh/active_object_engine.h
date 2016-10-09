//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif
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
    /*�������桱�Ĵ������ǰ��������̵߳Ĵ��������������߳�ʱ����ָ��
     *Ψһ�����������������������빹�캯������*/
    ActiveObjectEngine(char *pThreadName);
    virtual ~ActiveObjectEngine();

private:
    //list��ʵ��ԭ����ָ����У��������е�Ԫ����ҪƵ����ɾʱ����list����ɾЧ�ʸ��ߣ�������Ч�ʽϵ�
    //vector��ʵ��ԭ�������飬�������е�Ԫ�ز���ҪƵ����ɾʱ����vector�Ĳ���Ч�ʸ��ߣ�������ɾЧ�ʽϵ�
    std::list<SmartCmd> m_cmds;
    CRtnSemaphore * m_sem;
    bool m_running;
};

#endif