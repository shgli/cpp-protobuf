#ifndef _SE_CLASSFIELD_H
#define _SE_CLASSFIELD_H
#include "IField.h"
class ClassField:public IField
{
    public:
	typedef IField Base;
	virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
	virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
	virtual std::ostream& CodingByteSize(FormatStream& fos);
    public:
	ClassField(const std::string& name,int seqNo);
	virtual void Initialize( void );

    protected:
	virtual std::ostream& _CodingDeserialize(FormatStream& fos);
        //virtual std::ostream& _CodingByteSize(FormatStream& fos);
};
#endif
 
