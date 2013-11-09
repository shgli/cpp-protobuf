#ifndef _SE_ENUMFIELD_H
#define _SE_ENUMFIELD_H 
#include "IField.h"
class EnumField:public IField
{
    public:
	typedef IField Base;
	virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
	virtual std::ostream& CodingByteSize(FormatStream& fos);

	EnumField(const std::string& name,int seqNo);
    protected:
	virtual std::ostream& _CodingDeserialize(FormatStream& fos);
};
#endif//_SE_ENUMFIELD_H 
