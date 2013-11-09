#include "ClassField.h"
#include "FormatStream.h"
#include "GuardAble.h"
void ClassField::Initialize( void )
{
    Base::Initialize();
    mWireType = WireFormatLite::WIRETYPE_LENGTH_DELIMITED;
}

std::ostream& ClassField::CodingSerialize2Array(FormatStream& fos)
{
    BLOCK(fos)
    {
        fos<<"uint32 usize = (uint32)ByteSizeInternal(" + RefName() + ");"<<std::endl;
	fos<<"target = WireFormatLite::WriteTagToArray("<<SeqNo()<<", WireFormatLite::WIRETYPE_LENGTH_DELIMITED, target);"<<std::endl;
	fos<<"target = WireFormatLite::WriteUInt32NoTagToArray(usize,target);"<<std::endl;
	fos<<"target = Serialize2Array(target,"<<RefName()<<");"<<std::endl;
    }
}

std::ostream& ClassField::CodingSerialize2CodedStream(FormatStream& fos)
{
    BLOCK(fos)
    {
	fos<<"uint32 usize = (uint32)ByteSizeInternal(" + RefName() + ");"<<std::endl;
	fos<<"WireFormatLite::WriteTag("<<SeqNo()<<", WireFormatLite::WIRETYPE_LENGTH_DELIMITED, &cos);"<<std::endl;
	fos<<"WireFormatLite::WriteUInt32NoTag(usize,&cos);"<<std::endl;
	fos<<"Serialize2CodedStream(cos,"<<RefName()<<");"<<std::endl;
    }
}

std::ostream& ClassField::_CodingDeserialize(FormatStream& fos)
{
    return fos<<"DO_((DeserializeUser(cis,"<<RefName()<<")));"<<std::endl;
}

ClassField::ClassField(const std::string& name,int seqNo)
    :IField(name,seqNo)
{
}

std::ostream& ClassField::CodingByteSize(FormatStream& fos)
{
    BLOCK(fos)
    {
	fos<<"uint32 usize = (uint32)ByteSizeInternal("<<RefName()<<");"<<std::endl;
	return fos<<"totalSize += 1 + usize + WireFormatLite::UInt32Size(usize);"<<std::endl;
    }
}


