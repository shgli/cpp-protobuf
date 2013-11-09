#ifndef _SE_TYPEINFO_H
#define _SE_TYPEINFO_H
#include <string>
#include "FieldType.h"
#include "gcc.h"

class TypeInfo
{
public:
    static TypeInfo* Parse(tree decl);

    bool IsPointer()const { return mIsPointer;}
    FieldType Type() const { return mType;}
    TypeInfo* Detail(){return mDetail;}
    const TypeInfo* Detail()const{return mDetail;}
    tree InternalType()const { return mInternalType;}
    const std::string& Name() const {return mName;}
private:
    TypeInfo();

    FieldType mType;
    bool mIsPointer;
    TypeInfo *mDetail; //valid only for TYPE_ARRAY and TYPE_MAP
    tree mInternalType;
    std::string mName;

    static bool IsPointer(const std::string& qname);
    static bool IsArray(const std::string& qname);
    static bool IsMap(const std::string& qname);

    static const char* POINTER_NAMES[64];
    static const char* ARRAY_NAMES[64];
    static const char* MAP_NAMES[64];

    friend std::ostream& operator<<(std::ostream& os,const TypeInfo& ft);
};
#endif
