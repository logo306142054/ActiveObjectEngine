//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif�����active_object_engine.h
#pragma once
#include "stdlib.h"
#include "action_id.h"
class CMessage;

//����ģʽ�õ��Ľӿ�
class IAction
{
public:
    //����executeָ��
    virtual void Execute(CMessage *pMessage = NULL) = 0;

    virtual ~IAction() {}
};
