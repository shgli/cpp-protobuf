#include <cassert>
#include "diagnostics.h"
#include "Collector.h"
#include "ClassInfo.h"
#include "FieldInfo.h"
#include "MethodInfo.h"
#include "TypeInfo.h"
#include "Utils.h"
void Collector::CollectType(tree decl)
{
    if(AddDecl(decl))
    {
	tree main = TYPE_MAIN_VARIANT(TREE_TYPE(decl));
	for (tree d (TYPE_FIELDS (main));
		d != 0;
		d = TREE_CHAIN (d))
	{
	    if(TYPE_DECL == TREE_CODE (d) && !DECL_SELF_REFERENCE_P(decl))
	    {
		CollectType(d);
	    }
	}
    }
}

void Collector::Collect(tree ns)
{
    tree decl;
    cp_binding_level* level(NAMESPACE_LEVEL(ns));

    for(decl = level->names;
	decl != 0;
	decl = TREE_CHAIN(decl))
    {
	if(DECL_IS_BUILTIN(decl))
	{
	    continue;
	}
	else if(TYPE_DECL == TREE_CODE(decl))
	{
	    CollectType(decl);
	}
    }

    for(decl = level->namespaces;
	decl != 0;
	decl = TREE_CHAIN(decl))
    {
	if(DECL_IS_BUILTIN(decl))
	{
	    continue;
	}
	Collect(decl);
    }
}

bool Collector::AddDecl(tree decl)
{
    bool isFirst = false;
    tree type = TREE_TYPE(decl);
    if(RECORD_TYPE == TREE_CODE(type))
    {
	tree main = TYPE_MAIN_VARIANT(type);
	ClassInfo *pInfo = mClassInfoMap[main];
	if(0 == pInfo)
	{
	    pInfo = new ClassInfo(main);
	    mClassInfoMap[main] = pInfo;
	    isFirst = true;
	}
	mDeclInfoMap[decl] = pInfo;
    }
    else
    {
    }

    return isFirst;
}

void Collector::Collect(SerializeMetas& metas)
{
    Collect(global_namespace);

    //find out serialiable classes.
    auto itClassInfo = mDeclInfoMap.begin();
    for(auto serializableDecl : metas[global_namespace])
    {
	while(itClassInfo != mDeclInfoMap.end()
	       	&& (DECL_SOURCE_LOCATION(itClassInfo->first) < serializableDecl->Location()))
        {
	    ++itClassInfo; 
	} 

	if(itClassInfo != mDeclInfoMap.end())
	{
	    if((LOCATION_LINE(DECL_SOURCE_LOCATION(itClassInfo->first)) - LOCATION_LINE(serializableDecl->Location())) <= LOOSE_LIMIT)
	    {
		itClassInfo->second->IsSerializable(true);
	    }
	    else
	    {
		warn(serializableDecl->Location())<<" serializable decl  is too loose to be considered as an effective statement.";
	    }
	}
    }

    //complete serializable field and method
    for(auto metaPair : metas)
    {
	tree node = metaPair.first;
	itClassInfo = mDeclInfoMap.find(node);
	ClassInfo *pClassInfo = itClassInfo != mDeclInfoMap.end() ? itClassInfo->second : nullptr;
	if(node != global_namespace && nullptr != pClassInfo)
	{
	    if(pClassInfo->IsCurrentUnit())
	    {
		if(!pClassInfo->IsCollected())
		{
		    CollectBaseInfo(pClassInfo);
		    CollectFieldInfo(pClassInfo,metaPair.second);
		    CollectMethodInfo(pClassInfo,metaPair.second);
		    pClassInfo->IsCollected(true);
		}
	    }
	    else
	    {
		mDependencies.insert(pClassInfo->QName());
	    }
	}
    }//for
}

void Collector::CollectBaseInfo(ClassInfo* pInfo)
{
    // Traverse base information.
    //
    tree biv (TYPE_BINFO (pInfo->SyntaxTree()));
    size_t nBaseCount(biv ? BINFO_N_BASE_BINFOS (biv) : 0);

    for (size_t i (0); i < nBaseCount; i++)
    {
	tree bi (BINFO_BASE_BINFO (biv, i));
	tree type(TYPE_MAIN_VARIANT(BINFO_TYPE(bi)));
	auto pBaseInfo = mClassInfoMap[type];
	if(nullptr != pBaseInfo)
	{
	    pInfo->Bases().push_back(pBaseInfo);
	}
    }
}

void Collector::CollectFieldInfo(ClassInfo* pFieldInfo,const SerializeMetaSet& infos)
{
    //Collect fields
    std::set<tree,tree_comparator> fields;
    for (tree d (TYPE_FIELDS (pFieldInfo->SyntaxTree()));
	    d != 0;
	    d = TREE_CHAIN (d))
    {
	switch (TREE_CODE (d))
	{
	    case TYPE_DECL:
		{
		    break;
		}
	    case FIELD_DECL:
		{
		    if (!DECL_ARTIFICIAL (d))
			fields.insert (d);
		    break;
		}
	    default:
		{
		    fields.insert (d);
		    break;
		}
	}
    }

    auto itFieldDecl = fields.begin();
    bool isFinished = false;
    for(auto itMember = infos.begin(); itMember != infos.end();++itMember)
    {
	const SerializeField* pFieldMeta = dynamic_cast<const SerializeField*>((*itMember));
	if(nullptr != pFieldMeta)
	{
	    while(DECL_SOURCE_LOCATION(*itFieldDecl) < pFieldMeta->Location())
	    {
		itFieldDecl++;
		if(itFieldDecl == fields.end())
		{
		    isFinished = true;
		    break;
		}
	    }

	    if(isFinished)
            {
	       	break;
	    }

	    if(LOCATION_LINE(DECL_SOURCE_LOCATION(*itFieldDecl)) - LOCATION_LINE(pFieldMeta->Location()) > LOOSE_LIMIT)
	    {
		warn(pFieldMeta->Location()) << "serialize field declare is too loose to be ignored.";
	    }
	    else
	    {
		TypeInfo* pFieldType = TypeInfo::Parse(*itFieldDecl);
		if(nullptr != pFieldType && pFieldType->Type() != FieldType::EN_MAX_FIELD)
		{
		    if(pFieldType->Type() == FieldType::EN_USER_FIELD
			|| pFieldType->Type() == FieldType::EN_ARRAY_FIELD
			|| pFieldType->Type() == FieldType::EN_MAP_FIELD
		      )
		    {
			tree t = pFieldType->InternalType();
			if(nullptr == t)
			{ 
			    //muse b TYPE_ARRAY or TYPE_MAP
			    t = pFieldType->Detail()->InternalType();
			}

			if(nullptr != t)
			{
			    auto pClassInfo = mDeclInfoMap.find(t);
			    assert(mDeclInfoMap.end() != pClassInfo);
			    if(!pClassInfo->second->IsSerializable())
			    {
				error(pFieldMeta->Location())<<"type "<<pClassInfo->second->Name()<<" excepted serializable, but it's not!"<<std::endl;
				exit(-1);
			    }
			}
		    }

		    std::string name = GetNameByTree(*itFieldDecl);
		    pFieldInfo->Fields().push_back(FieldInfo(pFieldType,name,*pFieldMeta));
		}
	    }
	}
    }

}

void Collector::CollectMethodInfo(ClassInfo* pMethodInfo,const SerializeMetaSet& infos)
{
    std::set<tree,tree_comparator> methods;
    for (tree d (TYPE_METHODS (pMethodInfo->SyntaxTree())); d != 0; d = TREE_CHAIN (d))
    {
	if (!DECL_ARTIFICIAL (d))
	    methods.insert (d);
    }

    auto itMethodDecl = methods.begin();
    bool isFinished = false;
    for(auto itMember = infos.begin(); itMember != infos.end();++itMember)
    {
	const SerializeMethod* pMethodMeta = dynamic_cast<const SerializeMethod*>((*itMember));
	if(nullptr != pMethodMeta)
	{
	    while(DECL_SOURCE_LOCATION(*itMethodDecl) < pMethodMeta->Location())
	    {
		itMethodDecl++;
		if(itMethodDecl == methods.end())
		{
		    isFinished = true;
		    break;
		}
	    }

	    if(isFinished)
	    {
		break;
	    }

	    if(LOCATION_LINE(DECL_SOURCE_LOCATION(*itMethodDecl)) - LOCATION_LINE(pMethodMeta->Location()) > LOOSE_LIMIT)
	    {
		warn(pMethodMeta->Location()) << "serialize call back declare is too loose to be ignored."<<std::endl;
	    }
	    else
	    {
		tree tm = TREE_TYPE(*itMethodDecl);
		tree ret_type = TREE_TYPE(tm);
		if(METHOD_TYPE == TREE_CODE(tm) && VOID_TYPE == TREE_CODE(ret_type))
		{
		    int nargs = 0;
		    for(tree arg = TYPE_ARG_TYPES(tm); arg != NULL_TREE; arg = TREE_CHAIN(arg))
		    {
			if(void_type_node != TREE_VALUE(arg))
			{
			    nargs++;
			}
		    }

                    if( 1 == nargs)
		    {
			std::string name = GetNameByTree(*itMethodDecl);
			pMethodInfo->Methods()[pMethodMeta->MethodRule()] = new MethodInfo(name,pMethodMeta->MethodRule());
			continue;
		    }
		}
		error(pMethodMeta->Location()) <<"The signature of a  serialize call back should be void T::fun()"<<std::endl;
		exit(-1);
	    }
	}
    }
}

#ifdef _DEBUG
void Collector::PrintClassInfos()const
{
    std::cout<<"class infos:"<<std::endl;
    for(const auto& pClassInfo : ClassInfos())
    {
	std::cout<<pClassInfo.first<<":"<<pClassInfo.second->Name()<<std::endl;
    }

    std::cout<<std::endl<<"decl infos:"<<std::endl;
    for(const auto& declInfoPair : mDeclInfoMap)
    {
	std::cout<<declInfoPair.first<<":"<<declInfoPair.second->Name()<<std::endl;
    }

}
#endif

std::ostream& operator<<(std::ostream& os,const Collector& p)
{
    for(auto &pClassInfo : p.ClassInfos())
    {
	auto classInfo = pClassInfo.second;
	if(classInfo->IsSerializable() && classInfo->IsCurrentUnit())
	{
	    //decl
	    os<<"class "<<classInfo->Name();
	    bool isFirstSerializableBase = true;
	    for(auto &baseInfo : classInfo->Bases())
	    {
		if(baseInfo->IsSerializable())
		{
		    if(isFirstSerializableBase)
		    {
			os<<":";
			isFirstSerializableBase = false;
		    }
		    else
		    {
			os<<",";
		    }
		    os<<baseInfo->Name();
		}
	    }
	    os<<std::endl;
	    os<<"{"<<std::endl;

	    //fields
	    for(auto &fieldInfo : classInfo->Fields())
	    {
		os<<"    "
		    <<SerializeField::FieldTypeSpelling[fieldInfo.SInfo().FieldRule()]<<" "
		    <<fieldInfo.Type()<<" "
		    <<fieldInfo.Name()<<" ="
		    <<fieldInfo.SInfo().DefValue().Literal<<" =>"
		    <<fieldInfo.SInfo().SeqNo()<<";"
		    <<std::endl;
	    }

	    //methods
	    for(auto &methodInfo : classInfo->Methods())
	    {
                if(nullptr != methodInfo)
                {
		    os<<"    "<<SerializeMethod::MethodTypeSpelling[methodInfo->MethodRule()]<<":"<<methodInfo->Name()<<std::endl;
                }
	    }

	    //end
	    os<<"}"<<std::endl;
	}
    }
    return os;
}

