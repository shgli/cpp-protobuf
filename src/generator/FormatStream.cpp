#include "FormatStream.h"
FormatStream::FormatStream(std::ostream& os,uint8_t in)
    :mOstream(os)
    ,mIndent(in)
{
}

FormatStream::BlockGuard::BlockGuard(FormatStream& fos)
    :mStream(fos)
{
    mStream<<"{"<<std::endl;
    mStream.Indent();    
}

FormatStream::BlockGuard::BlockGuard(FormatStream& fos,const std::string& expr)
    :mStream(fos)
{
    mStream<<expr<<std::endl;
    mStream<<"{"<<std::endl;
    mStream.Indent();    
}

FormatStream::BlockGuard::~BlockGuard()
{
    mStream.Outdent();
    mStream<<"}"<<std::endl;
}

FormatStream::CaseGuard::CaseGuard(FormatStream& fos,const std::string& expr)
    :mStream(fos)
{
    mStream<<"case "<<expr<<":"<<std::endl;
    mStream.Indent()<<"{"<<std::endl;
    mStream.Indent();
}

FormatStream::CaseGuard::~CaseGuard()
{
    mStream.Outdent()<<"}"<<std::endl;
    mStream<<"break;"<<std::endl;
    mStream.Outdent();
}

