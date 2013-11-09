#ifndef _SE_METHODINFO_H
#define _SE_METHODINFO_H
#include <string>
#include "Metas.h"
class MethodInfo
{
public:
    MethodInfo(const std::string& name,SerializeMethod::enMethodRule rule)
	:mName(name)
	,mMethodRule(rule)
    {}

    const std::string& Name()const { return mName;}
    SerializeMethod::enMethodRule MethodRule()const { return mMethodRule;}
private:
    std::string mName;
    SerializeMethod::enMethodRule mMethodRule;
};
#endif

