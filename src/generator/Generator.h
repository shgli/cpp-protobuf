#ifndef _SE_GENERATOR_H
#define _SE_GENERATOR_H
#include <vector>
#include <string>
#include "Class.h"

typedef std::vector<Class::Ptr> ClassesT;
typedef std::vector<Class::Ptr> DependenciesT;
class Generator
{
public:
    bool Do(const ClassesT& allClass,const DependenciesT& dependency,const std::string& fileName) const;
};
#endif
 
