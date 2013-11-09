#include "Plugin.h"
#include "MetaParser.h"
#include "Generator.h"
#include "Collector.h"
#include "FieldBuilder.h"
#include "ClassInfo.h"
#include "TypeInfo.h"
#include "FieldInfo.h"
#include "MethodInfo.h"
using namespace std;

int plugin_is_GPL_compatible;

Plugin::Plugin()
{
    mMetaParser.reset(new MetaParser());
    mCollector.reset(new Collector());
    mGenerator.reset(new Generator());
}

void Plugin::ParseMeta()
{
    mMetaParser->Parse();
}

void Plugin::CollectTypes()
{
    auto metas = mMetaParser->Metas();
    mCollector->Collect(metas);
}

void Plugin::Generate( void )
{

    auto classInfos = mCollector->ClassInfos();
    auto dependenies = mCollector->Dependencies();

    ClassesT classes;
    DependenciesT dependenyClasses;
    BuildGenerateInfos(classes,dependenyClasses,classInfos,dependenies);
    mGenerator->Do(classes,dependenyClasses,main_input_filename);
}

void Plugin::BuildGenerateInfos(ClassesT& classes,DependenciesT& dependencies,const ClassInfoMap& classInfos,const DependencySet dset)
{
    std::map<std::string,Class::Ptr> classMap;
    FieldBuilder builder;
    for(auto classInfoPair : classInfos)
    {
	auto& pClassInfo = classInfoPair.second;
	if(nullptr != pClassInfo && pClassInfo->IsSerializable())
	{
	    Class::Ptr pClass(new Class(pClassInfo->QName()));
	    classes.push_back(pClass);

	    //field
	    for(const FieldInfo& fieldInfo : pClassInfo->Fields())
	    {
		const TypeInfo& typeInfo = fieldInfo.Type();
	        IField::Ptr pField;
		if(typeInfo.IsPointer())
		{
		    if(nullptr != typeInfo.Detail())
		    {//map/array
			if(EN_ARRAY_FIELD == typeInfo.Type())
			{
			    const TypeInfo& detail = *typeInfo.Detail();
			    if(detail.IsPointer())
			    {
				pField = builder.BuildPtrArrayPtr(detail.Type(),fieldInfo.Name(),fieldInfo.SInfo().SeqNo());
			    }
			    else
			    {
				pField = builder.BuildArrayPtr(detail.Type(),fieldInfo.Name(),fieldInfo.SInfo().SeqNo());
			    }
			}
			else
			{
			    //not support
			}
		    }
		    else
		    {
			pField = builder.BuildPtr(typeInfo.Type(),fieldInfo.Name(),fieldInfo.SInfo().SeqNo());
		    }
		}
		else
		{
		    if(nullptr != typeInfo.Detail())
		    { //map/array
		        if(EN_ARRAY_FIELD == typeInfo.Type())
		        {
			    const TypeInfo& detail = *typeInfo.Detail();
			    if(detail.IsPointer())
			    {
				pField = builder.BuildPtrArray(detail.Type(),fieldInfo.Name(),fieldInfo.SInfo().SeqNo());
			    }
			    else
			    {
				pField = builder.BuildArray(detail.Type(),fieldInfo.Name(),fieldInfo.SInfo().SeqNo());
			    }
			}
			else
			{
			    //not support

			}
		    }
		    else
		    {
			pField = builder.BuildField(typeInfo.Type(),fieldInfo.Name(),fieldInfo.SInfo().SeqNo());
		    }
		}
	        pClass->Fields().push_back(pField);
	    }

	    //methods
	    for(int rule = (int)SerializeMethod::EN_OnSerializing 
		    ;rule != SerializeMethod::EN_MaxRule
		    ;++rule)
	    {
		MethodInfo* pMethodInfo = pClassInfo->Methods()[rule];
		if(nullptr != pMethodInfo)
		{
		    pClass->SetCallback(GetCallbackType((SerializeMethod::enMethodRule)rule),pMethodInfo->Name());
		}
	    }

	    //base infos
	    for(auto pBaseInfo : pClassInfo->Bases())
	    {
		if(nullptr != pBaseInfo && pBaseInfo->IsSerializable())
		{
		    auto itBaseClass = classMap.find(pBaseInfo->QName());
		    if(itBaseClass != classMap.end())
		    {
			pClass->Bases().push_back(itBaseClass->second);

		    }
		    else
		    {
			assert(false);
		    }
		}
	    }
	    classMap[pClassInfo->QName()] = pClass;
	}//if
    }//for class infos

    for(const std::string& dependency : dset)
    {
	auto itClass = classMap.find(dependency);
	if(itClass != classMap.end())
	{
	    dependencies.push_back(itClass->second);
	}
	else
	{
	    assert(false);
	}
    }//for dependency
}

SerializeCallback Plugin::GetCallbackType(SerializeMethod::enMethodRule rule)
{
    switch(rule)
    {
	case SerializeMethod::EN_OnSerializing:
	    return SEC_ONSERIALIZING;
	case SerializeMethod::EN_OnSerialized:
	    return SEC_ONSERIALIZED;
	case SerializeMethod::EN_OnDeserializing:
	    return SEC_ONDESERIALIZEING;
	case SerializeMethod::EN_OnDeserialized:
	    return SEC_ONDESERIALIZED;
	default:
	    return SEC_NONE;
    }
}
