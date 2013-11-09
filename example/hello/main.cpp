#include "Person.h"
#include "Person.se.h"

void main(int argc,char** argv)
{
    Person p;
    p.Name("shgli");
    p.Friends().push_back(2);
    p.Friends().push_back(3);

    char buffer[512] = {0};
    Serialization::Serialize(p,buffer,sizeof(buffer));

    Person p1 = Serialization::DeSerialize(buffer,sizeof(buffer));

    std::cout<<"Hello "<<p1.Name()<<std::endl;

    return 0;
}

