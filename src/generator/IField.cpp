#include "IField.h"
#include "IFieldDecorator.h"
#include "FormatStream.h"
#include "GuardAble.h"
const std::string IField::gFormatTypeSpelling[6] = {"WIRETYPE_VARINT",
    "WIRETYPE_FIXED64",
    "WIRETYPE_LENGTH_DELIMITED",
    "WIRETYPE_START_GROUP",
    "WIRETYPE_END_GROUP",
    "WIRETYPE_FIXED32"};

IField::IField(const std::string& name,int seqNo)
    :mDecorator(nullptr)
    ,mName(name)
    ,mSeqNo(seqNo)
    ,mQName("obj." + name)
{
}

void IField::Initialize( void )
{
    mRefName = QName();
    mPtrName = "&" + QName();
    mWireType = WireFormatLite::WIRETYPE_VARINT;
}

void IField::QNameSameAsName( void )
{
    mQName = mName;
    Initialize();
}

const std::string& IField::RefName( void ) const
{
    if(nullptr == mDecorator)
    {
	return mRefName;
    }
    else
    {
	return mDecorator->RefName();
    }
}

const std::string& IField::PtrName( void ) const
{
    if(nullptr == mDecorator)
    {
	return mPtrName;
    }
    else
    {
	return mDecorator->PtrName();
    }
}

std::ostream& IField::CodingByteSize(FormatStream& fos)
{
    return (fos<<"totalSize += ");
}

std::ostream& IField::CodingDeserialize(FormatStream& fos)
{
    CASE(fos,SeqNo())
    {
	IF(fos,"WireFormatLite::GetTagWireType(tag) == WireFormatLite::" + FormatLiteType())
	{
            BLOCK_EX(fos,"parse_" + Name() + ":")
	    {
	        _CodingDeserialize(fos);
	    }

	    if(nullptr != mNext)
	    {
		IF(fos,"cis.ExpectTag(" + boost::lexical_cast<std::string>(WireFormatLite::MakeTag(mNext->SeqNo(),mNext->WireType())) + ")")
		{
		    fos<<"goto parse_"<<mNext->Name()<<";"<<std::endl;
		}
	    }
	    else
	    {
		IF(fos,"cis.ExpectAtEnd()")
		{
		    fos<<"break;"<<std::endl;
		}
	    }
        }
	ELSE(fos)
	{
            return fos<<"goto handle_uninterpreted;"<<std::endl;
	}
    }
}

