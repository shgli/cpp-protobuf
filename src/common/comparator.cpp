#include "Comparator.h"
extern int Compare(const std::string& l,const std::string& r)
{
    int i = 0;
    for(;i < l.length() && i < r.length();++i)
    {
        int cmp = (l[i] | 32) - (r[i] | 32);
        if(0 != cmp)
        {
    	return cmp;
        }
    }
    return l.length() - r.length();
}
