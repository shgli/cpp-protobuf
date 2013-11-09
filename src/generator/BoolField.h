#ifndef _SE_BOOL_H 
#define _SE_BOOL_H 
#include "IField.h"
class BoolField:public IField
{
    public:
	typedef IField Base;
	virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
	virtual std::ostream& CodingByteSize(FormatStream& fos);
    public:
	BoolField(const std::string& name,int seqNo);

    protected:
	virtual std::ostream& _CodingDeserialize(FormatStream& fos);
};
#endif//_SE_SINTFIELD_H 

