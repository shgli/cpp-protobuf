#include "PointerDecorator.h"
#include "FormatStream.h"
#include "GuardAble.h"
PointerDecorator::PointerDecorator(IField::Ptr pDecorated)
    :IFieldDecorator(pDecorated->Name(),pDecorated)
     ,mCreateIfNull(true)
{}

void PointerDecorator::Initialize( void )
{
    mRefName = "*" + Decorated()->QName();
    mPtrName = Decorated()->QName();
}

std::ostream& PointerDecorator::CodingSerialize2Array(FormatStream& fos)
{
    IF(fos,"nullptr != " + PtrName())
    {
	return Base::CodingSerialize2Array(fos);
    }
}

std::ostream& PointerDecorator::CodingSerialize2CodedStream(FormatStream& fos)
{
    IF(fos,"nullptr != " + PtrName())
    {
	return Base::CodingSerialize2CodedStream(fos);
    }
}

std::ostream& PointerDecorator::_CodingDeserialize(FormatStream& fos)
{
    if(CreateIfNull())
    {
	IF(fos,"nullptr == " + PtrName())
	{
	    fos<<PtrName()<<" = SerializeCreate("<<"*obj."<<Name()<<");"<<std::endl;
	}
    }

    return Base::_CodingDeserialize(fos);
}

std::ostream& PointerDecorator::CodingByteSize(FormatStream& fos)
{
    IF(fos,"nullptr != " + PtrName())
    {
	return Base::CodingByteSize(fos);
    }
}


