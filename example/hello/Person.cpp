#include "Person.h"
#include <iostream>
void Person::OnSerialing()
{
    std::cout<<"Hello: "<<__FUNCTION__<<std::endl;
}
  
void OnSerialized()
{
    std::cout<<"Hello: "<<__FUNCTION__<<std::endl;
}

void OnDeserializing()
{
    std::cout<<"Hello: "<<__FUNCTION__<<std::endl;
}

void OnDeserialized()
{
    std::cout<<"Hello: "<<__FUNCTION__<<std::endl;
}

