#ifndef _SE_CLASS_INFO_H
#define _SE_CLASS_INFO_H
#include <string>
#include "Metas.h"
class FieldInfo;
class MethodInfo;
class ClassInfo;

typedef std::vector<FieldInfo> FieldInfos;
typedef std::vector<ClassInfo*> BaseInfos;
typedef MethodInfo* MethodInfos[SerializeMethod::EN_MaxRule];

class ClassInfo
{
public:
    ClassInfo(tree t);

    bool IsSerializable() const{return mIsSerializable;}
    void IsSerializable(bool s) { mIsSerializable = s;}

    const FieldInfos& Fields()const { return mFieldInfos;}
    FieldInfos& Fields() { return mFieldInfos;}

    const MethodInfos& Methods()const {return mMethodInfos;}
    MethodInfos& Methods() { return mMethodInfos;}

    const BaseInfos& Bases()const{return mBaseInfos;}
    BaseInfos& Bases() { return mBaseInfos;}

    const std::string& FileName()const { return mFileName;}
    bool IsCurrentUnit()const { return mIsCurrentUnit;}
    tree SyntaxTree()const {return mSyntaxTree;}
    bool IsCollected()const { return mIsCollected;}
    void IsCollected(bool collect) { mIsCollected = collect;}

    const std::string& Name()const { return mName;}
    const std::string& QName()const { return mQName;}

private:
    MethodInfos mMethodInfos;
    FieldInfos mFieldInfos;
    BaseInfos  mBaseInfos;
    bool mIsSerializable;
    tree mSyntaxTree;
    std::string mFileName;
    std::string mName;
    std::string mQName;

    bool mIsCurrentUnit;
    bool mIsCollected;
};
#endif

