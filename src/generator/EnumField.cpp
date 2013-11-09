#include "EnumField.h"
#include "FormatStream.h"
EnumField::EnumField(const std::string& name,int seqNo)
    :Base(name,seqNo)
{}

std::ostream& EnumField::CodingSerialize2Array(FormatStream& fos)
{
    return (fos<<"target = WireFormatLite::WriteEnumToArray("<<SeqNo()<<","<<RefName()<<",target);"<<std::endl);
}

std::ostream& EnumField::CodingSerialize2CodedStream(FormatStream& fos)
{
    return (fos<<"WireFormatLite::WriteEnum("<<SeqNo()<<","<<RefName()<<",&cos);"<<std::endl);
}

std::ostream& EnumField::_CodingDeserialize(FormatStream& fos)
{
    fos<<"int value"<<std::endl;
    fos<<"DO_((WireFormatLite::ReadPrimitive<int, WireFormatLite::TYPE_ENUM>(&cis,&value)));"<<std::endl;
    return fos<<RefName()<<"=value;"<<std::endl;
}

std::ostream& EnumField::CodingByteSize(FormatStream& fos)
{
    return Base::CodingByteSize(fos)<<"1 + WireFormatLite::EnumSize("<<RefName()<<");"<<std::endl;
}
