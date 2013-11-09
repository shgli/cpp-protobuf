#include "gcc.h"
#include "Utils.h"
std::string GetDeclNamespace(tree decl)
{
    std::string s, tmp;

    for (tree scope (CP_DECL_CONTEXT (decl));
	    scope != global_namespace;
	    scope = CP_DECL_CONTEXT (scope))
    {
	tmp = "::";
        if(CLASS_TYPE_P(scope))
	{
	    scope = TYPE_NAME(scope);
	    tmp += GetNameByTree(scope);
	}
	else
	{
	    tmp += GetNameByTree(scope);
	}
    	tmp += s;
	s.swap (tmp);
    }

    return s;
}

std::string GetNameByTree(tree decl)
{
    tree id = DECL_NAME(decl);
    const char *name = id ? IDENTIFIER_POINTER (id) : "<unnamed>"; 
    return  std::string(name);
}

