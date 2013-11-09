#include "ArrayDecorator.h"
#include "FormatStream.h"
#include "GuardAble.h"
ArrayDecorator::ArrayDecorator(const std::string& name,IField::Ptr pDecorated)
    :Base(name,pDecorated)
{
    pDecorated->SetDecorator(nullptr);
}
std::ostream& ArrayDecorator::CodingSerialize2Array(FormatStream& fos)
{
    FOR(fos,"auto& v : " + RefName())
    {
	return Decorated()->CodingSerialize2Array(fos);
    }
}

std::ostream& ArrayDecorator::CodingSerialize2CodedStream(FormatStream& fos)
{
    FOR(fos,"auto& v : " + RefName())
    {
	return Decorated()->CodingSerialize2CodedStream(fos);
    }
}

std::ostream& ArrayDecorator::CodingByteSize(FormatStream& fos)
{
    if(0 == Decorated()->FixedSize())
    {
	FOR(fos,"auto& v : " + RefName())
	{
	    return Decorated()->CodingByteSize(fos);
	}
    }
    else
    {
        return fos<<"totalSize += "<<(1 + Decorated()->FixedSize()) << " * ("<<RefName()<<").size();"<<std::endl;
    }
}

std::ostream& ArrayDecorator::_CodingDeserialize(FormatStream& fos)
{
   BLOCK(fos)
   {
       fos<<"auto v = InsertPlaceholder("<<RefName()<<");"<<std::endl;
       Decorated()->_CodingDeserialize(fos)<<std::endl;
       return fos<<"if (cis.ExpectTag("<<WireFormatLite::MakeTag(SeqNo(),WireType())<<")) goto parse_"<<Name()<<";"<<std::endl;
   }
}

