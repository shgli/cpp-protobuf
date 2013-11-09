#include "tt.h"
#include "../../include/serialize.h"
#include <boost/assign.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Serialization;

int main(int argc,char** argv)
{
    {
        Base1 b;
        b.SetInt(3);
        b.SetDouble(4.0);
        fstream out("pp.txt",ios::out | ios::trunc);
        Serialize(out,b);
    }

    {
        fstream in("pp.txt");
        Base1 c;
        Deserialize(in,c);

        std::cout<<c.GetInt()<<std::endl;
        std::cout<<c.GetDouble()<<std::endl;
    }

    {
        using namespace boost::assign;
        Derived d;
        d.SetDValue(8.0);
        d.SetInt(38);
        d.SetDouble(832.0);
        d.GetNest().IntValue() = 3;
        d.GetNest().DoubleValue() = 28.0;
        d.GetNestPtr() = nullptr;
        d.GetString() = "shgli";
        d.PtrString() = nullptr;
        d.GetVecInt() += 3,2,3;
        d.GetVecIntPtr().push_back(new int(3));
        d.GetVecIntPtr().push_back(new int(5));
        d.GetVecPtrInt() = new vector<int>();
        *d.GetVecPtrInt() += 2,9,82;
        d.GetVecPtrIntPtr() = new std::vector<int*>();
        d.GetVecPtrIntPtr()->push_back(new int(2));
        d.GetVecPtrIntPtr()->push_back(new int(5));

        fstream out("derived.txt",ios::out);
        Serialize(out,d);
    }

    std::cout<<"Derived:"<<std::endl;

    {
        ifstream in("derived.txt");
        if(in.is_open())
        {
            Derived des;
            des.GetNestPtr() = nullptr;
            des.GetVecPtrInt() = nullptr;
            des.GetVecPtrIntPtr() = nullptr;
            Deserialize(in,des);
            std::cout<<des.GetDValue()<<std::endl;
            std::cout<<des.GetInt()<<std::endl;
            std::cout<<des.GetDouble()<<std::endl;
            std::cout<<des.GetNest().IntValue()<<std::endl;
            std::cout<<des.GetNest().DoubleValue()<<std::endl;
            std::cout<<des.GetString()<<std::endl;
            std::copy(des.GetVecInt().begin(),des.GetVecInt().end(),std::ostream_iterator<int>(std::cout," "));
            std::cout<<std::endl;
            std::for_each(des.GetVecIntPtr().begin(),des.GetVecIntPtr().end(),[](int* v){std::cout<<*v<<" ";});
            std::cout<<std::endl;
            std::copy(des.GetVecPtrInt()->begin(),des.GetVecPtrInt()->end(),std::ostream_iterator<int>(std::cout," "));
            std::cout<<std::endl;
            std::for_each(des.GetVecPtrIntPtr()->begin(),des.GetVecPtrIntPtr()->end(),[](int* v){std::cout<<*v<<" ";});
            std::cout<<std::endl;
        }
    }
return 0;
}

