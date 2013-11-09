#include "UIntField.h"
#include "FormatStream.h"

std::ostream& UIntField::CodingSerialize2Array(FormatStream& fos)
{
    return (fos<<"target = WireFormatLite::WriteUInt"<<mBits<<"("<<SeqNo()<<","<<RefName()<<",target);"<<std::endl);
}

std::ostream& UIntField::CodingSerialize2CodedStream(FormatStream& fos)
{
    return (fos<<"WireFormatLite::WriteUInt"<<mBits<<"ToArray("<<SeqNo()<<","<<RefName()<<",&cos);"<<std::endl);
}

std::ostream& UIntField::_CodingDeserialize(FormatStream& fos)
{
    return fos<<"DO_((WireFormatLite::ReadPrimitive<int"<<mBits<<", WireFormatLite::TYPE_SINT"<<mBits<<">(&cis,"<<PtrName()<<")));"<<std::endl;
}

std::ostream& UIntField::CodingByteSize(FormatStream& fos)
{
    return Base::CodingByteSize(fos)<<"1 + WireFormatLite::UInt"<<mBits<<"Size("<<RefName()<<");"<<std::endl;
}

UIntField::UIntField(const std::string& name,uint8 nBits,int seqNo)
    :IField(name,seqNo)
    ,mBits(nBits)
{
    assert(8 == mBits || 16 == nBits || 32 == nBits || 64 == nBits);
    if(mBits < 32) mBits = 32;
}


