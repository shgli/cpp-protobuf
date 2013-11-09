#include "DoubleField.h"
#include "FormatStream.h"
void DoubleField::Initialize( void )
{
    Base::Initialize();
    mWireType = WireFormatLite::WIRETYPE_FIXED64;
}

std::ostream& DoubleField::CodingSerialize2Array(FormatStream& fos)
{
    return (fos<<"target = WireFormatLite::WriteDoubleToArray("<<SeqNo()<<","<<RefName()<<",target);"<<std::endl);
}

std::ostream& DoubleField::CodingSerialize2CodedStream(FormatStream& fos)
{
    return (fos<<"WireFormatLite::WriteDouble("<<SeqNo()<<","<<RefName()<<",&cos);"<<std::endl);
}

std::ostream& DoubleField::_CodingDeserialize(FormatStream& fos)
{
    return fos<<"DO_((WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(&cis,"<<PtrName()<<")));"<<std::endl;
}

std::ostream& DoubleField::CodingByteSize(FormatStream& fos)
{
    return Base::CodingByteSize(fos)<<"1 + 8;"<<std::endl;
}

DoubleField::DoubleField(const std::string& name,int seqNo)
    :IField(name,seqNo)
{
}


