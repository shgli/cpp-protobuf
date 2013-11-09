#include "indent.h"
#include <iostream>
std::ostream& operator<<(std::ostream& os,const indent& in)
{
    for(int i = 0; i < in.indents_;++i)
    {
	os<<"    ";
    }
    return os;
}
