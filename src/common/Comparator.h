#ifndef _SE_COMPARATOR_H
#define _SE_COMPARATOR_H
#include "gcc.h"
#include <string>
struct tree_comparator
{
    bool operator() (tree x, tree y) const
    {
	tree xd = TYPE_NAME(x);
	tree yd = TYPE_NAME(y);
	if(0 == xd) xd = x;
	if(0 == yd) yd = y;
	location_t xl (DECL_SOURCE_LOCATION (xd));
	location_t yl (DECL_SOURCE_LOCATION (yd));

	//std::cout<<"cmp("<<x<<","<<y<<")==("<<xl<<","<<yl<<")"<<std::endl;
	return xl < yl;
    }
};

extern int Compare(const std::string& l,const std::string& r);
#endif 

