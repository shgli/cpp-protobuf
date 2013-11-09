#ifndef _SE_CLASS_H
#define _SE_CLASS_H
#include <string>
#include <vector>
#include "IField.h"
#include <stdint.h>
enum SerializeCallback
{
    SEC_NONE = 0x0000,
    SEC_ONSERIALIZING = 0x0001,
    SEC_ONSERIALIZED  = 0x0002,
    SEC_ONDESERIALIZEING = 0x0004,
    SEC_ONDESERIALIZED   = 0x0008
};

class FortmatStream;
class Class
{
public:
    typedef std::shared_ptr<Class> Ptr;

    Class(const std::string& name);
    void CodingDeclare(FormatStream& fos) const;
    void Coding(FormatStream& fos) const;

    typedef std::vector<IField::Ptr> FieldsT;
    typedef std::vector<Class::Ptr> BasesT;

    FieldsT& Fields() { return mFields;}
    const FieldsT& Fields() const { return mFields;}
    BasesT& Bases() { return mBases;}
    const BasesT& Bases() const { return mBases;}

    void SetCallback(SerializeCallback callback,const std::string& name);
    const std::string& GetCallbackName(SerializeCallback callback) const;

    const std::string& Name( void )const { return mName;}
private:
    void CodingSerialize2Array(FormatStream& fos) const;
    void CodingSerialize2CodedStream(FormatStream& fos) const;
    void CodingDeserialize(FormatStream& fos) const;
    void CodingByteSize(FormatStream& fos) const;

    bool HasSerializing() const { return mCallbacks & SEC_ONSERIALIZING;}
    bool HasSerialized() const { return mCallbacks & SEC_ONSERIALIZED;}
    bool HasDeserializing() const { return mCallbacks & SEC_ONDESERIALIZEING;}
    bool HasDeserialized()const { return mCallbacks & SEC_ONDESERIALIZED;}
    void PreSerialize(FormatStream& fos) const;
    void PostSerialize(FormatStream& fos) const;
    void PreDeSerialize(FormatStream& fos) const;
    void PostDeSerialize(FormatStream& fos) const;
private:
    std::string mName;
    std::string mSerialize2ArrayDeclare;
    std::string mSerialize2CodedStreamDeclare;
    std::string mDeserializeDeclare;
    std::string mByteSizeDeclare;

    FieldsT mFields;
    BasesT mBases;
    uint8_t mCallbacks;
    std::string mCallbackNames[4];
};
#endif
 
