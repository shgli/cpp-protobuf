#include "Person.pb.h"
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc,char** argv)
{
    {
        Person p;
        p.set_age(32);
        p.add_friends(1);
        p.add_friends(2);
        p.set_salary(3.2);
        p.set_i32(83);
        p.set_name("shgli");
        p.mutable_one()->set_room("720");
        p.mutable_one()->set_streat("hong shang");

        fstream out("person.pb", ios::out | ios::binary | ios::trunc);
        p.SerializeToOstream(&out);
        out.close();
    }
    {
        fstream input("person.pb", ios::in | ios::binary);
        Person person;
        person.ParseFromIstream(&input);
        std::cout<<person.age()<<std::endl;
        std::cout<<person.name()<<std::endl;
        std::cout<<person.one().room()<<std::endl;
        std::cout<<person.one().streat()<<std::endl;
    }
    return 0;
}

