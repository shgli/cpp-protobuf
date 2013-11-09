#ifndef _SE_POINTERDECORATOR_H
#define _SE_POINTERDECORATOR_H
#include "IFieldDecorator.h"
class PointerDecorator:public IFieldDecorator
{
public:
    typedef IFieldDecorator Base;
    typedef std::shared_ptr<PointerDecorator> Ptr;

    PointerDecorator(IField::Ptr pDecorated);
    virtual void Initialize( void );

    virtual std::ostream& CodingSerialize2Array(FormatStream& fos);
    virtual std::ostream& CodingSerialize2CodedStream(FormatStream& fos);
    virtual std::ostream& CodingByteSize(FormatStream& fos);

    void CreateIfNull(bool create) { mCreateIfNull = create; }
    bool CreateIfNull( void ) const { return mCreateIfNull; }
protected:
    virtual std::ostream& _CodingDeserialize(FormatStream& fos);
    virtual const std::string& RefName( void ) const { return mRefName;}
    virtual const std::string& PtrName( void ) const { return mPtrName;}

private:
    bool mCreateIfNull;
};
#endif//_SE_POINTERDECORATOR_H
