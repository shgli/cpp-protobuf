#ifndef _PERSON_H
#define _PERSON_H
#include <string>

#pragma protobuf serializable
class Person
{
    #pragma protobuf field required =3 1
    int mId;

    #pragma protobuf field optional 2
    std::string mName;

public:
    #pragma protobuf method onserialized
    void OnSerialized();

    #pragma protobuf method onserializing
    void OnSerializing();

    #pragma protobuf method ondeserialized
    void OnDeserialized();

    #pragma protobuf method ondeserializing
    void OnDeserializing();
};
#endif

