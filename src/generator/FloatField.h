#ifndef _SE_FLOATFIELD_H
#define _SE_FLOATFIELD_H 
#include "IField.h"
class FloatField:public IField
{
    public:
	typedef IField Base;
	virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
	virtual std::ostream& CodingByteSize(FormatStream& fos);
    public:
	FloatField(const std::string& name,int seqNo);
	virtual void Initialize( void );

    protected:
	virtual std::ostream& _CodingDeserialize(FormatStream& fos);
	virtual int FixedSize( void ) const { return 4; }
};
#endif

