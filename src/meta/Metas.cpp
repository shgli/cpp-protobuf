#include <iostream>
#include "Metas.h"
#include "diagnostics.h"

const char* SerializeMethod::MethodTypeSpelling[SerializeMethod::EN_MaxRule] = {"onserializing","onserialized","ondeserializing","ondeserialized"} ;
const char* SerializeField::FieldTypeSpelling[SerializeField::EN_MaxRule] = {"required","optional","repeated"};

void PrintSerializeMetas(const SerializeMetas& metas)
{
    for(const auto& metaPair : metas)
    {
	std::cout<<metaPair.first<<":"<<std::endl;

	for(const auto& pMetaInfo : metaPair.second)
	{
	    std::cout<<"    ";
	    info(pMetaInfo->Location());
	    if(pMetaInfo->Is<Serializable>())
	    {
		std::cout<<"serialiable";
	    }
	    else if(pMetaInfo->Is<SerializeField>())
	    {
		std::cout<<"field";
	    }
	    else
	    {
		std::cout<<"method";
	    }
	    std::cout<<std::endl;
	}

	std::cout<<std::endl;
    }
}
