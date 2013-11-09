#include <iostream>
#include "TypeInfo.h"
#include "Utils.h"
const char* TypeInfo::POINTER_NAMES[64] =
{
    "::std::shared_ptr",
    "::std::unique_ptr",
    "::std::weak_ptr",
    "::boost::shared_ptr",
    "::boost::unique_ptr",
    "::boost::weak_ptr",
    nullptr
};
const char* TypeInfo::ARRAY_NAMES[64] =
{
    "::std::vector",
    "::std::list",
    "::std::set",
    "::std::multi_set",
    "::boost::unordered_set",
    nullptr
};

const char* TypeInfo::MAP_NAMES[64]
{
    "::std::map",
    "::std::multi_map",
    "::std::unordered_map",
    "::boost::unordered_map",
    nullptr
};

bool TypeInfo::IsPointer(const std::string& qname)
{
    for(const char** name = &POINTER_NAMES[0]; nullptr != *name;++name)
    {
	if(qname == *name)
	{
	    return true;
	}
    }

    return false;
}

bool TypeInfo::IsArray(const std::string& qname)
{
    for(const char** name = &ARRAY_NAMES[0]; nullptr != *name;++name)
    {
	if(qname == *name)
	{
	    return true;
	}
    }

    return false;
}

bool TypeInfo::IsMap(const std::string& qname)
{
    for(const char** name = &MAP_NAMES[0]; nullptr != *name;++name)
    {
	if(qname == *name)
	{
	    return true;
	}
    }

    return false;

}

std::ostream& operator<<(std::ostream& os,const TypeInfo& ft)
{
    switch(ft.Type())
    {
        case EN_BOOL_FIELD:
            os<<"bool ";
            break;
        case EN_UINT8_FIELD:
            os<<"uint8 ";
            break;
        case EN_UINT16_FIELD:
            os<<"uint16 ";
            break;
        case EN_UINT32_FIELD:
            os<<"uint32 ";
            break;
        case EN_UINT64_FIELD:
            os<<"uint64 ";
            break;
        case EN_SINT8_FIELD:
            os<<"sint8 ";
            break;
        case EN_SINT16_FIELD:
            os<<"sint16 ";
            break;
        case EN_SINT32_FIELD:
            os<<"sint32 ";
            break;
        case EN_SINT64_FIELD:
            os<<"sint64 ";
            break;
        case EN_FLOAT_FIELD:
            os<<"float ";
            break;
        case EN_DOUBLE_FIELD:
            os<<"double ";
            break;
        case EN_ENUM_FIELD:
            os<<"enum ";
            break;
        case EN_STRING_FIELD:
            os<<"string ";
            break;
        case EN_ARRAY_FIELD:
            os<<"array<"<<*(ft.Detail())<<"> ";
            break;
        case EN_MAP_FIELD:
	    os<<"map<";
            break;
	case EN_USER_FIELD:
	    {
		tree decl = TYPE_NAME(ft.InternalType());
	        os<<GetNameByTree(decl);
                break;
	    }
	default:
	    break;
    }

    if(ft.IsPointer())
    {
        os<<"* ";
    }
    return os;
}

TypeInfo::TypeInfo()
    :mType(EN_MAX_FIELD)
    ,mIsPointer(false)
    ,mDetail(nullptr)
    ,mInternalType(nullptr)
{
}

TypeInfo* TypeInfo::Parse(tree decl)
{
    if(nullptr == decl || FIELD_DECL != TREE_CODE(decl))
    {
        return nullptr;
    }

    TypeInfo *ret = new TypeInfo();
    TypeInfo *tmp = ret;
    tree type = TREE_TYPE(decl);
    bool more = false;
    do
    {
        more = false;
        switch(TREE_CODE(type))
        {
            case POINTER_TYPE:
                tmp->mIsPointer = true;
                type = TREE_TYPE(type);
                more = true;
                break;
            case BOOLEAN_TYPE:
                tmp->mType = EN_BOOL_FIELD;
                break;
            case ENUMERAL_TYPE:
                tmp->mType = EN_ENUM_FIELD;
                break;
            case INTEGER_TYPE:
                {
                    if(TYPE_UNSIGNED(type))
                    {
                        switch(TYPE_PRECISION(type))
                        {
                            case 8:
                                tmp->mType = EN_UINT8_FIELD;
                                break;
                            case 16:
                                tmp->mType = EN_UINT16_FIELD;
                                break;
                            case 32:
                                tmp->mType = EN_UINT32_FIELD;
                                break;
                            case 64:
                                tmp->mType = EN_UINT64_FIELD;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch(TYPE_PRECISION(type))
                        {
                            case 8:
                                tmp->mType = EN_SINT8_FIELD;
                                break;
                            case 16:
                                tmp->mType = EN_SINT16_FIELD;
                                break;
                            case 32:
                                tmp->mType = EN_SINT32_FIELD;
                                break;
                            case 64:
                                tmp->mType = EN_SINT64_FIELD;
                                break;
                            default:
                                break;
                        }

                    }
                }
               break;
           case REAL_TYPE:
               if(32 == TYPE_PRECISION(type))
               {
                   tmp->mType = EN_FLOAT_FIELD;
               }
               else if(64 == TYPE_PRECISION(type))
               {
                   tmp->mType = EN_DOUBLE_FIELD;
               }
               break;
           case REFERENCE_TYPE:
               {
                   type = TREE_TYPE(type);
                   more = true;
                   break;
               }
               break;
           case ARRAY_TYPE:
               {
                   tmp->mType = EN_ARRAY_FIELD;
                   type = TREE_TYPE(type);
                   tmp->mDetail = new TypeInfo();
                   tmp = tmp->mDetail;
                   more = true;
               }
               break;
           case RECORD_TYPE:
               {
		   tree ti(TYPE_TEMPLATE_INFO(type));
		   if(nullptr == ti)
		   {
		       tmp->mType = EN_USER_FIELD;
		       tmp->mInternalType = TYPE_MAIN_VARIANT(type);
		   }
		   else
		   {
		       tree main(TYPE_MAIN_VARIANT(type));
                       tree td(TYPE_NAME(main));
                       std::string qname = GetDeclNamespace(td) + "::";
		       qname += GetNameByTree(td);
		       if(qname == "::std::string" || "::std::basic_string" == qname) 
		       {
			   tmp->mType = EN_STRING_FIELD;
			   break;
		       }
		       else if(IsPointer(qname))
		       {
			   //pointer
			   tmp->mIsPointer = true;
		       }
		       else if(IsArray(qname))
		       {
			   //array
			   tmp->mType = EN_ARRAY_FIELD;
		       }
		       else if(IsMap(qname))
		       {
			   //map
			   tmp->mType = EN_MAP_FIELD;
		       }
		       else
		       {
			   tmp = nullptr;
			   break;
		       }

		       if(nullptr != tmp)
		       {
			   tmp->mName = qname;
		       }

		       tree args (INNERMOST_TEMPLATE_ARGS (TI_ARGS (ti)));                                                                                                                                        
		       size_t n = TREE_VEC_LENGTH (args);
		       if(n > 1)
		       {
			   tmp->mDetail = new TypeInfo(); 
			   type = (TREE_VEC_ELT (args, 0));   
			   tmp = tmp->Detail();
			   more = true;
		       }
		   }
               }
               break;
           default:
               break;
        }

	if(!more && nullptr != tmp && 0 == tmp->mName.length())
	{
	    tree td = TYPE_NAME(type);
            std::string qname = GetDeclNamespace(td) + "::";
	    qname += GetNameByTree(td);
            tmp->mName = qname;
	}
    }while(more);

    return ret;
}

