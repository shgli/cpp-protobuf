#ifndef _SE_FIELDINFO_H
#define _SE_FIELDINFO_H
#include <string>

class TypeInfo;
class SerializeField;
class SerializeField;
class FieldInfo
{
public:
    FieldInfo(TypeInfo *t,const std::string& name,const SerializeField& field)
	:mType(t)
	,mName(name)
	,mField(&field)
    {}

    const SerializeField& SInfo()const { return *mField;}
    TypeInfo& Type() { return *mType;}
    const TypeInfo& Type()const { return *mType;}
    const std::string& Name()const { return mName;}
private:
    TypeInfo* mType;
    std::string mName;
    const SerializeField* mField;
};
#endif

