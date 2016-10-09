//未避免头文件的重复包含，所有头文件都必须用#pragma once或者宏定义包含起来
//较老的gcc版本可能不支持#pragma，使用宏定义包含能起到同样的效果，就是麻烦一些
//在文件末尾记得不要漏了#endif，详见active_object_engine.h
#pragma once

/*
信号量封装类（从公司挪出来的类名）
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
实现临界资源的自动lock和unlock
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

//定义两个自动lock和unlock的宏，方便使用
#define RTN_AUTO_LOCK(P) CAutoLock autoLock_##P(P)
#define RTN_AUTO_UNLOCK(P) autoLock_##P.~CAutoLock()