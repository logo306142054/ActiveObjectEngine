//未避免头文件的重复包含，所有头文件都必须用#pragma once或者宏定义包含起来
//较老的gcc版本可能不支持#pragma，使用宏定义包含能起到同样的效果，就是麻烦一些
//在文件末尾记得不要漏了#endif，详见active_object_engine.h
#pragma once
#include "comm_type_def.h"

class CMessage
{
public:
    //触发的事件类型
    WORD m_wMessageId;
    //保存触发事件的事件源指针
    void* m_pMessageSource;
    //存放事件相关的数据
    void* m_pMessageData;
    //错误信息
    WORD m_wError;

    CMessage() : CMessage(0, 0, NULL, NULL)
    {
    }

    CMessage(WORD wMessageId, WORD wError, void* pMessageData = NULL, void* pMessageSource = NULL)
    {
        m_wMessageId = wMessageId;
        m_pMessageData = pMessageData;
        m_pMessageSource = NULL;
        m_wError = wError;
    }
};
