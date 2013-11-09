#include "FormatStream.h"
#include "FloatField.h"
void FloatField::Initialize( void )
{
    Base::Initialize();
    mWireType = WireFormatLite::WIRETYPE_FIXED32;
}

std::ostream& FloatField::CodingSerialize2Array(FormatStream& fos)
{
    return (fos<<"target = WireFormatLite::WriteFloatToArray("<<SeqNo()<<","<<RefName()<<",target);"<<std::endl);
}

std::ostream& FloatField::CodingSerialize2CodedStream(FormatStream& fos)
{
    return (fos<<"WireFormatLite::WriteFloat("<<SeqNo()<<","<<RefName()<<",&cos);"<<std::endl);
}

std::ostream& FloatField::_CodingDeserialize(FormatStream& fos)
{
    return fos<<"DO_((WireFormatLite::ReadPrimitive<float, WireFormatLite::TYPE_FLOAT>(&cis,"<<PtrName()<<")));"<<std::endl;
}

std::ostream& FloatField::CodingByteSize(FormatStream& fos)
{
    return Base::CodingByteSize(fos)<<"1 + 4;"<<std::endl;
}

FloatField::FloatField(const std::string& name,int seqNo)
    :IField(name,seqNo)
{
}


