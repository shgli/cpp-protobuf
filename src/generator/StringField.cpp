#include "StringField.h"
#include "FormatStream.h"

void StringField::Initialize( void )
{
    Base::Initialize();
    mWireType = WireFormatLite::WIRETYPE_LENGTH_DELIMITED;
}

std::ostream& StringField::CodingSerialize2Array(FormatStream& fos)
{
    return (fos<<"target = WireFormatLite::WriteStringToArray("<<SeqNo()<<","<<RefName()<<",target);"<<std::endl);
}

std::ostream& StringField::CodingSerialize2CodedStream(FormatStream& fos)
{
    return (fos<<"WireFormatLite::WriteString("<<SeqNo()<<","<<RefName()<<",&cos);"<<std::endl);
}

std::ostream& StringField::_CodingDeserialize(FormatStream& fos)
{
    fos<<"DO_(WireFormatLite::ReadString(&cis,"<<PtrName()<<" ));"<<std::endl;
    return fos<<"WireFormat::VerifyUTF8String(("<<RefName()<<").data(), ("<<RefName()<<").length(),WireFormat::PARSE);"<<std::endl;
}

std::ostream& StringField::CodingByteSize(FormatStream& fos)
{
    return Base::CodingByteSize(fos)<<"1 + WireFormatLite::StringSize("<<RefName()<<");"<<std::endl;
}

StringField::StringField(const std::string& name,int seqNo)
    :IField(name,seqNo)
{
}


