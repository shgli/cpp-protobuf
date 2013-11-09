#include <boost/filesystem.hpp>
#include <fstream>
#include "Generator.h"
#include "Class.h"
#include "FormatStream.h"
#include "GuardAble.h"
bool Generator::Do(const std::vector<Class::Ptr>& allClass,const std::vector<Class::Ptr>& dependencies,const std::string& baseName)const
{
    namespace fs = boost::filesystem;
    std::string fileName = baseName + ".se.cpp";
    std::ofstream sfile(fileName,std::ios_base::out);
    if(sfile.is_open())
    {
	FormatStream fos(sfile);
	fos<<"#define private public"<<std::endl;
        fos<<"#define DO_(EXPRESSION) if (!(EXPRESSION)) return false"<<std::endl;
	fos<<"#include \""<<baseName<<"\""<<std::endl;
	fos<<"#include \"utils.h\""<<std::endl;
	fos<<"#include <google/protobuf/wire_format_lite.h>"<<std::endl;
	fos<<"#include <google/protobuf/wire_format.h>"<<std::endl;
	fos<<"#include <google/protobuf/wire_format_lite_inl.h>"<<std::endl;
	fos<<"#include \"serialize.h\""<<std::endl;

	NAMESPACE(fos,"Serialization")
	{
	    fos<<"using namespace google::protobuf::io;"<<std::endl;
	    fos<<"using namespace google::protobuf::internal;"<<std::endl;
	    fos<<"using namespace google::protobuf;"<<std::endl;

	    for(const auto& pClass : dependencies)
	    {
		if(nullptr != pClass)
		{
		    pClass->CodingDeclare(fos);
		}
	    }

	    for(const auto& pClass : allClass)
	    {
		if(nullptr != pClass)
		{
		    pClass->CodingDeclare(fos);
		}
	    }

	    for(const auto& pClass : allClass)
	    {
		if(nullptr != pClass)
		{
		    pClass->Coding(fos);
		}
	    }
	}

	fos<<"#undef DO_"<<std::endl;
	fos<<"#undef private"<<std::endl;
    }
    else
    {
	std::cerr<<"can not open file "<<fileName<<" for write"<<std::endl;
	return false;
    }
}

