//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif�����active_object_engine.h
#pragma once

/*
�ź�����װ�ࣨ�ӹ�˾Ų������������
*/
class CRtnSemaphore
{
public:
    void Lock();
    void UnLock();
    void RegMSem(char *pSemName, int flag);
    void UnRegSem();
public:
    CRtnSemaphore();
    ~CRtnSemaphore();
private:
    int index;
};

/*
ʵ���ٽ���Դ���Զ�lock��unlock
*/
class CAutoLock
{
public:
    CAutoLock(CRtnSemaphore *pSemaphore)
    {
        m_pSemaphore = pSemaphore;
        m_pSemaphore->Lock();
    }
    ~CAutoLock()
    {
        m_pSemaphore->UnLock();
    }
private:
    CRtnSemaphore * m_pSemaphore;
};

//���������Զ�lock��unlock�ĺ꣬����ʹ��
#define RTN_AUTO_LOCK(P) CAutoLock autoLock_##P(P)
#define RTN_AUTO_UNLOCK(P) autoLock_##P.~CAutoLock()