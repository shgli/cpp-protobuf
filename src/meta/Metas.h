#ifndef _SE_METAS_H
#define  _SE_METAS_H
#include "SerializeMeta.h"
class Serializable:public SerializeMeta
{
public:
    Serializable(location_t loc)
	:SerializeMeta(loc)
    {}
};

class SerializeField:public SerializeMeta
{
public:
    enum enFieldRule
    {
	EN_Required,
	EN_Optional,
	EN_Repeated,
        EN_MaxRule
    };

    SerializeField(location_t loc,enFieldRule fieldRule,const DefaultValue& defaultValue,int seqNo)
	:SerializeMeta(loc)
	,mFieldRule(fieldRule)
        ,mDefaultValue(defaultValue)
	,mSeqNo(seqNo)
    {}

    const DefaultValue& DefValue() const { return mDefaultValue;}
    int SeqNo() const { return mSeqNo;}

    enFieldRule FieldRule()const { return mFieldRule;}
private:
    DefaultValue mDefaultValue;
    enFieldRule mFieldRule;
    int mSeqNo;
public:
    static const char* FieldTypeSpelling[EN_MaxRule];
};

class SerializeMethod:public SerializeMeta
{
public:
    enum enMethodRule
    {
	EN_OnSerializing,
	EN_OnSerialized,
	EN_OnDeserializing,
	EN_OnDeserialized,
        EN_MaxRule
    };

    SerializeMethod(location_t loc,enMethodRule methodRule)
	:SerializeMeta(loc)
	,mMethodRule(methodRule)
    {}

    enMethodRule MethodRule() const { return mMethodRule;}
private:
    enMethodRule mMethodRule;

public:
    static const char* MethodTypeSpelling[EN_MaxRule];
};

extern void PrintSerializeMetas(const SerializeMetas& metas);

#endif


