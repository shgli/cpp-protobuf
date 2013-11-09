#ifndef _SE_ARRAYDECORATOR_H
#define _SE_ARRAYDECORATOR_H
#include "IFieldDecorator.h"
class ArrayDecorator:public IFieldDecorator
{
public:
    typedef IFieldDecorator Base;
    ArrayDecorator(const std::string& name,IField::Ptr pDecorated);

    virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
    virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
    virtual std::ostream& CodingByteSize(FormatStream& fos);

protected:
    virtual std::ostream& _CodingDeserialize(FormatStream& fos);
};
#endif
