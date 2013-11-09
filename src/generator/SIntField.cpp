#include "SIntField.h"
#include "FormatStream.h"
#include "GuardAble.h"
std::ostream& SIntField::CodingSerialize2Array(FormatStream& fos)
{
    return (fos<<"target = WireFormatLite::WriteSInt"<<mBits<<"ToArray("<<SeqNo()<<","<<RefName()<<",target);"<<std::endl);
}

std::ostream& SIntField::CodingSerialize2CodedStream(FormatStream& fos)
{
    return (fos<<"WireFormatLite::WriteSInt"<<mBits<<"("<<SeqNo()<<","<<RefName()<<",&cos);"<<std::endl);
}

std::ostream& SIntField::_CodingDeserialize(FormatStream& fos)
{
    return fos<<"DO_((WireFormatLite::ReadPrimitive<int"<<mBits<<", WireFormatLite::TYPE_SINT"<<mBits<<">(&cis,"<<PtrName()<<")));"<<std::endl;
}

std::ostream& SIntField::CodingByteSize(FormatStream& fos)
{
    return Base::CodingByteSize(fos)<<"1 + WireFormatLite::SInt"<<mBits<<"Size("<<RefName()<<");"<<std::endl;
}

SIntField::SIntField(const std::string& name,uint8 nBits,int seqNo)
    :IField(name,seqNo)
    ,mBits(nBits)
{
    assert(8 == mBits || 16 == nBits || 32 == nBits || 64 == nBits);
    if(mBits < 32) mBits = 32;
}


