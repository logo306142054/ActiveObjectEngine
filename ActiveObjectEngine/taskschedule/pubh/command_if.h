//未避免头文件的重复包含，所有头文件都必须用#pragma once或者宏定义包含起来
//较老的gcc版本可能不支持#pragma，使用宏定义包含能起到同样的效果，就是麻烦一些
//在文件末尾记得不要漏了#endif
#ifndef _COMMAND_IF_H_
#define _COMMAND_IF_H_
#include "action_if.h"
#include "to_string_if.h"

class ICommand : public IAction, public IToString
{
public:
    //接收execute指令
    virtual void Execute(CMessage *pMessage = NULL) = 0;

    //返回该类实例的字符串信息，用于定位
    virtual const ostringstream & ToString() = 0;

    virtual ~ICommand(){}
};

#endif