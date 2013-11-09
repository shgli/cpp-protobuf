#ifndef _SE_IFIELD_H
#define _SE_IFIELD_H
#include <string>
#include <memory>
#include <google/protobuf/wire_format_lite.h>
using namespace google::protobuf::internal;

class IFieldDecorator;
class FormatStream;
class IField
{
    public:
	typedef std::shared_ptr<IField> Ptr;

	IField(const std::string& name,int seqNo);
	virtual ~IField() {}

	virtual void Initialize( void );

	virtual std::ostream& CodingSerialize2Array(FormatStream& fos) = 0;
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos) = 0;
	virtual std::ostream& CodingDeserialize(FormatStream& fos);
	virtual std::ostream& CodingByteSize(FormatStream& fos) = 0;

	void SetDecorator(IFieldDecorator* pDecorator) { mDecorator = pDecorator;}

	void SetNext(IField::Ptr next) { mNext = next;}
	virtual const std::string& FormatLiteType( void ) const { return gFormatTypeSpelling[mWireType];}
	const std::string& Name( void ) const { return mName; }

	const std::string QName( void ) const { return mQName;}

	void QNameSameAsName( void );

	int SeqNo( void ) { return mSeqNo; }
	void SeqNo(int seqNo) { mSeqNo = seqNo; }
	virtual const std::string& RefName( void ) const;
	virtual const std::string& PtrName( void ) const;


	WireFormatLite::WireType WireType( void ) const { return mWireType; }
	virtual std::ostream& _CodingDeserialize(FormatStream& fos) = 0;

	virtual int FixedSize( void ) const { return 0; }

    protected:
	IFieldDecorator* mDecorator;
	std::string mName;
	std::string mQName;
	std::string mRefName;
	std::string mPtrName;
	WireFormatLite::WireType mWireType;
	int mSeqNo;

	IField::Ptr mNext;

	static const std::string gFormatTypeSpelling[6];
};
#endif//_SE_IFIELD_H
