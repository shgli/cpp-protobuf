#ifndef _SE_IFIELDDECORATOR_H
#define _SE_IFIELDDECORATOR_H
#include <cassert>
#include "IField.h"
class IFieldDecorator:public IField
{
    public:
	IFieldDecorator(const std::string& name,IField::Ptr pDecorated)
	    :IField(name,-1)
	    ,mDecorated(pDecorated)
	{
	    assert(nullptr != mDecorated);
	    SeqNo(pDecorated->SeqNo());
	    mDecorated->SetDecorator(this);
	}

	virtual std::ostream& CodingSerialize2Array(FormatStream& fos) { return mDecorated->CodingSerialize2Array(fos);}
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos) { return mDecorated->CodingSerialize2CodedStream(fos);}
	//virtual std::ostream& CodingDeserialize(FormatStream& fos) { return mDecorated->CodingDeserialize(fos);}
	virtual std::ostream& CodingByteSize(FormatStream& fos) { return mDecorated->CodingByteSize(fos);}

    protected:
	IField::Ptr Decorated( void ) { return mDecorated; }

	virtual const std::string& FormatLiteType( void ) const { return mDecorated->FormatLiteType();}
        virtual std::ostream& _CodingDeserialize(FormatStream& fos) { return mDecorated->_CodingDeserialize(fos);}

    private:
	friend class IField;
	IField::Ptr mDecorated;
};
#endif
