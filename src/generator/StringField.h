#ifndef _SE_STRINGFIELD_H
#define _SE_STRINGFIELD_H 
#include "IField.h"
class StringField:public IField
{
    public:
	typedef IField Base;
	virtual void Initialize( void );
	virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
	virtual std::ostream& CodingByteSize(FormatStream& fos);
    public:
	StringField(const std::string& name,int seqNo);

    protected:
	virtual std::ostream& _CodingDeserialize(FormatStream& fos);
};
#endif//_SE_SINTFIELD_H 

