#include "BoolField.h"
#include "FormatStream.h"

std::ostream& BoolField::CodingSerialize2Array(FormatStream& fos)
{
    return (fos<<"target = WireFormatLite::WriteBoolToArray("<<SeqNo()<<","<<RefName()<<",target);"<<std::endl);
}

std::ostream& BoolField::CodingSerialize2CodedStream(FormatStream& fos)
{
    return (fos<<"WireFormatLite::WriteBool("<<SeqNo()<<","<<RefName()<<",&cos);"<<std::endl);
}

std::ostream& BoolField::_CodingDeserialize(FormatStream& fos)
{
    return fos<<"DO_((WireFormatLite::ReadPrimitive<bool, WireFormatLite::TYPE_BOOL>(&cis,"<<PtrName()<<")));"<<std::endl;
}

std::ostream& BoolField::CodingByteSize(FormatStream& fos)
{
    return Base::CodingByteSize(fos)<<"1 + WireFormatLite::BoolSize("<<RefName()<<");"<<std::endl;
}

BoolField::BoolField(const std::string& name,int seqNo)
    :IField(name,seqNo)
{
}


