#ifndef _PERSON_H
#define _PERSON_H
#include <core.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

Serializable
class Person
{
    Field(required,1,3) //Field(repeated,seq=1,def=3)
    int mId;
    Field(optional,2,"shgli") 
    string mName;
    Field(repeated,3)
    vector<int> mFriends;
public:
    Method(OnSerializing)
    void OnSerialing();
  
    Method(OnSerialized)
    void OnSerialized();

    Method(OnDeserializing)
    void OnDeserializing();

    Method(OnDeserialized)
    void OnDeserialized();

    int Id() const { return mId; }
    void Id(int id) { mId = id; }

    const string& Name()const { return mName;}
    void Name(const string name) { mName = name;}

    vector<int> Friends() { return mFriends; }
};
#endif
 
