#ifndef _SE_SINTFIELD_H
#define _SE_SINTFIELD_H 
#include "IField.h"
class SIntField:public IField
{
    public:
	typedef IField Base;
	virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
	virtual std::ostream& CodingByteSize(FormatStream& fos);
    public:
	SIntField(const std::string& name,uint8_t nSize,int seqNo);

    protected:
	virtual std::ostream& _CodingDeserialize(FormatStream& fos);
    private:
	uint32_t mBits;
};
#endif//_SE_SINTFIELD_H 

