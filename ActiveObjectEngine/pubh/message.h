//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif�����active_object_engine.h
#pragma once
#include "comm_type_def.h"

class CMessage
{
public:
    //�������¼�����
    WORD m_wMessageId;
    //���津���¼����¼�Դָ��
    void* m_pMessageSource;
    //����¼���ص�����
    void* m_pMessageData;
    //������Ϣ
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
