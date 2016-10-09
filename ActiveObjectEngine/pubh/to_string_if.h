//未避免头文件的重复包含，所有头文件都必须用#pragma once或者宏定义包含起来
//较老的gcc版本可能不支持#pragma，使用宏定义包含能起到同样的效果，就是麻烦一些
//在文件末尾记得不要漏了#endif，详见active_object_engine.h
#pragma once
#include <sstream>

using namespace std;

class IToString
{
public:
    virtual const ostringstream & ToString() = 0;

    virtual ~IToString() {}
};