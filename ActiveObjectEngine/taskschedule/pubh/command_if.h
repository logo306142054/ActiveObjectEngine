//δ����ͷ�ļ����ظ�����������ͷ�ļ���������#pragma once���ߺ궨���������
//���ϵ�gcc�汾���ܲ�֧��#pragma��ʹ�ú궨���������ͬ����Ч���������鷳һЩ
//���ļ�ĩβ�ǵò�Ҫ©��#endif
#ifndef _COMMAND_IF_H_
#define _COMMAND_IF_H_
#include "action_if.h"
#include "to_string_if.h"

class ICommand : public IAction, public IToString
{
public:
    //����executeָ��
    virtual void Execute(CMessage *pMessage = NULL) = 0;

    //���ظ���ʵ�����ַ�����Ϣ�����ڶ�λ
    virtual const ostringstream & ToString() = 0;

    virtual ~ICommand(){}
};

#endif