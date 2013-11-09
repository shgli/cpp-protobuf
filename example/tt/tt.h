#ifndef _TT_H
#define _TT_H
#include <string>
#include <vector>
#include <iostream>

#pragma protobuf serializable
class Base1
{
private:
    #pragma protobuf field required =3 1
    int mIntValue;

    #pragma protobuf field optional =0.2 2
    double mDoubleValue;

public:
    void SetInt(int v) { mIntValue = v; }
    void SetDouble(double v) { mDoubleValue = v;}

    int GetInt() { return mIntValue;}
    double GetDouble() { return mDoubleValue;}
    #pragma protobuf method onserialized
    void OnSerialized_()
    {
        std::cout<<"Base1 Serialized"<<std::endl;
    }
};

struct Base2
{
    int mIntValue1;
};

typedef Base1 Base;

#pragma protobuf serializable
struct Derived:public Base,public Base2
{
    #pragma protobuf field optional =56.0 3
    double mDValue;

    void SetDValue(double d) { mDValue = d;}
    double GetDValue() { return mDValue; }

    #pragma protobuf serializable
    struct Nest
    {
        #pragma protobuf field required =2.0 1
        int mIntValue;
	int& IntValue(){return mIntValue;}

        #pragma protobuf field optional =3.0 2
        double mDoubleValue;
	double& DoubleValue(){return mDoubleValue;}
    };

    typedef Nest MyNest;
    #pragma protobuf field required =7 4
    MyNest mNest;

    MyNest& GetNest() { return mNest; }

    #pragma protobuf field required  5   
    std::string mString;
    std::string& GetString() { return mString; }

    #pragma protobuf field required  6   
    std::string *mPtrString;
    std::string*& PtrString() { return mPtrString;}

    #pragma protobuf field required  7   
    std::vector<int> mVecInt;
    std::vector<int>& GetVecInt() { return mVecInt;}

    #pragma protobuf field required  8
    std::vector<int>* mVecPtrInt;
    std::vector<int>*& GetVecPtrInt() { return mVecPtrInt;}

    #pragma protobuf field required  9
    std::vector<int*> mVecIntPtr;
    std::vector<int*>& GetVecIntPtr() { return mVecIntPtr;}

    #pragma protobuf field required  10
    std::vector<int*> *mVecPtrIntPtr;
    std::vector<int*>*& GetVecPtrIntPtr() { return mVecPtrIntPtr;}

    #pragma protobuf field required 11
    MyNest* mNestPtr;
    MyNest*& GetNestPtr() { return mNestPtr;}

    #pragma protobuf method onserializing
    void OnSerializing()
    {
        std::cout<<"Derived Serializing"<<std::endl;
    }

};
#endif

