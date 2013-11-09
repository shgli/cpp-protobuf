#define private public
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
#include "tt.h"
#include "utils.h"
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include "serialize.h"
namespace Serialization
{
    using namespace google::protobuf::io;
    using namespace google::protobuf::internal;
    using namespace google::protobuf;
    uint8* Serialize2Array(uint8* target,::Base1& obj);
    bool Serialize2CodedStream(io::CodedOutputStream& cos,::Base1& obj);
    bool DeserializeInternal(io::CodedInputStream& cis,::Base1& obj);
    int ByteSizeInternal(const ::Base1& obj);

    uint8* Serialize2Array(uint8* target,::Derived& obj);
    bool Serialize2CodedStream(io::CodedOutputStream& cos,::Derived& obj);
    bool DeserializeInternal(io::CodedInputStream& cis,::Derived& obj);
    int ByteSizeInternal(const ::Derived& obj);

    uint8* Serialize2Array(uint8* target,::Derived::Nest& obj);
    bool Serialize2CodedStream(io::CodedOutputStream& cos,::Derived::Nest& obj);
    bool DeserializeInternal(io::CodedInputStream& cis,::Derived::Nest& obj);
    int ByteSizeInternal(const ::Derived::Nest& obj);

    uint8* Serialize2Array(uint8* target,::Base1& obj)
    {
        //serialize mIntValue
        target = WireFormatLite::WriteSInt32ToArray(1,obj.mIntValue,target);
        //serialize mDoubleValue
        target = WireFormatLite::WriteDoubleToArray(2,obj.mDoubleValue,target);
        obj.::Base1::OnSerialized_();
        return target;
    }

    bool Serialize2CodedStream(io::CodedOutputStream& cos,::Base1& obj)
    {
        WireFormatLite::WriteSInt32(1,obj.mIntValue,&cos);
        WireFormatLite::WriteDouble(2,obj.mDoubleValue,&cos);
        obj.::Base1::OnSerialized_();
        return true;
    }

    bool DeserializeInternal(io::CodedInputStream& cis,::Base1& obj)
    {
        ::google::protobuf::uint32 tag;
        while((tag = cis.ReadTag()) != 0)
        {
            switch(WireFormatLite::GetTagFieldNumber(tag))
            {
                case 1:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                        {
                            parse_mIntValue:
                            {
                                DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&obj.mIntValue)));
                            }
                            if(cis.ExpectTag(17))
                            {
                                goto parse_mDoubleValue;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 2:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_FIXED64)
                        {
                            parse_mDoubleValue:
                            {
                                DO_((WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(&cis,&obj.mDoubleValue)));
                            }
                            if(cis.ExpectAtEnd())
                            {
                                break;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                default:
                {
                    handle_uninterpreted:
                    if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_END_GROUP)
                    {
                        return true;
                    }
                }
            }
        }
        return true;
    }

    int ByteSizeInternal(const ::Base1& obj)
    {
        int totalSize = 0;
        totalSize += 1 + WireFormatLite::SInt32Size(obj.mIntValue);
        totalSize += 1 + 8;
        return totalSize;
    }


    uint8* Serialize2Array(uint8* target,::Derived& obj)
    {
        obj.::Derived::OnSerializing();
        target = WireFormatLite::WriteUInt32NoTagToArray((uint32)ByteSizeInternal(static_cast<::Base1&>(obj)),target);
        target = Serialize2Array(target,static_cast<::Base1&>(obj));
        //serialize mDValue
        target = WireFormatLite::WriteDoubleToArray(3,obj.mDValue,target);
        //serialize mNest
        {
            uint32 usize = (uint32)ByteSizeInternal(obj.mNest);
            target = WireFormatLite::WriteTagToArray(4, WireFormatLite::WIRETYPE_LENGTH_DELIMITED, target);
            target = WireFormatLite::WriteUInt32NoTagToArray(usize,target);
            target = Serialize2Array(target,obj.mNest);
        }
        //serialize mString
        target = WireFormatLite::WriteStringToArray(5,obj.mString,target);
        //serialize mPtrString
        if(nullptr != obj.mPtrString)
        {
            target = WireFormatLite::WriteStringToArray(6,*obj.mPtrString,target);
        }
        //serialize mVecInt
        for(auto& v : obj.mVecInt)
        {
            target = WireFormatLite::WriteSInt32ToArray(7,v,target);
        }
        //serialize mVecPtrInt
        if(nullptr != obj.mVecPtrInt)
        {
            for(auto& v : *obj.mVecPtrInt)
            {
                target = WireFormatLite::WriteSInt32ToArray(8,v,target);
            }
        }
        //serialize mVecIntPtr
        for(auto& v : obj.mVecIntPtr)
        {
            if(nullptr != v)
            {
                target = WireFormatLite::WriteSInt32ToArray(9,*v,target);
            }
        }
        //serialize mVecPtrIntPtr
        if(nullptr != obj.mVecPtrIntPtr)
        {
            for(auto& v : *obj.mVecPtrIntPtr)
            {
                if(nullptr != v)
                {
                    target = WireFormatLite::WriteSInt32ToArray(10,*v,target);
                }
            }
        }
        //serialize mNestPtr
        if(nullptr != obj.mNestPtr)
        {
            {
                uint32 usize = (uint32)ByteSizeInternal(*obj.mNestPtr);
                target = WireFormatLite::WriteTagToArray(11, WireFormatLite::WIRETYPE_LENGTH_DELIMITED, target);
                target = WireFormatLite::WriteUInt32NoTagToArray(usize,target);
                target = Serialize2Array(target,*obj.mNestPtr);
            }
        }
        return target;
    }

    bool Serialize2CodedStream(io::CodedOutputStream& cos,::Derived& obj)
    {
        obj.::Derived::OnSerializing();
        WireFormatLite::WriteUInt32NoTag((uint32)ByteSizeInternal(static_cast<::Base1&>(obj)),&cos);
        Serialize2CodedStream(cos,static_cast<::Base1&>(obj));
        WireFormatLite::WriteDouble(3,obj.mDValue,&cos);
        {
            uint32 usize = (uint32)ByteSizeInternal(obj.mNest);
            WireFormatLite::WriteTag(4, WireFormatLite::WIRETYPE_LENGTH_DELIMITED, &cos);
            WireFormatLite::WriteUInt32NoTag(usize,&cos);
            Serialize2CodedStream(cos,obj.mNest);
        }
        WireFormatLite::WriteString(5,obj.mString,&cos);
        if(nullptr != obj.mPtrString)
        {
            WireFormatLite::WriteString(6,*obj.mPtrString,&cos);
        }
        for(auto& v : obj.mVecInt)
        {
            WireFormatLite::WriteSInt32(7,v,&cos);
        }
        if(nullptr != obj.mVecPtrInt)
        {
            for(auto& v : *obj.mVecPtrInt)
            {
                WireFormatLite::WriteSInt32(8,v,&cos);
            }
        }
        for(auto& v : obj.mVecIntPtr)
        {
            if(nullptr != v)
            {
                WireFormatLite::WriteSInt32(9,*v,&cos);
            }
        }
        if(nullptr != obj.mVecPtrIntPtr)
        {
            for(auto& v : *obj.mVecPtrIntPtr)
            {
                if(nullptr != v)
                {
                    WireFormatLite::WriteSInt32(10,*v,&cos);
                }
            }
        }
        if(nullptr != obj.mNestPtr)
        {
            {
                uint32 usize = (uint32)ByteSizeInternal(*obj.mNestPtr);
                WireFormatLite::WriteTag(11, WireFormatLite::WIRETYPE_LENGTH_DELIMITED, &cos);
                WireFormatLite::WriteUInt32NoTag(usize,&cos);
                Serialize2CodedStream(cos,*obj.mNestPtr);
            }
        }
        return true;
    }

    bool DeserializeInternal(io::CodedInputStream& cis,::Derived& obj)
    {
        DeserializeUser(cis,static_cast<::Base1&>(obj));
        ::google::protobuf::uint32 tag;
        while((tag = cis.ReadTag()) != 0)
        {
            switch(WireFormatLite::GetTagFieldNumber(tag))
            {
                case 3:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_FIXED64)
                        {
                            parse_mDValue:
                            {
                                DO_((WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(&cis,&obj.mDValue)));
                            }
                            if(cis.ExpectTag(34))
                            {
                                goto parse_mNest;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 4:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                        {
                            parse_mNest:
                            {
                                DO_((DeserializeUser(cis,obj.mNest)));
                            }
                            if(cis.ExpectTag(42))
                            {
                                goto parse_mString;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 5:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                        {
                            parse_mString:
                            {
                                DO_(WireFormatLite::ReadString(&cis,&obj.mString ));
                                WireFormat::VerifyUTF8String((obj.mString).data(), (obj.mString).length(),WireFormat::PARSE);
                            }
                            if(cis.ExpectTag(48))
                            {
                                goto parse_mPtrString;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 6:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                        {
                            parse_mPtrString:
                            {
                                if(nullptr == obj.mPtrString)
                                {
                                    obj.mPtrString = SerializeCreate(*obj.mPtrString);
                                }
                                DO_(WireFormatLite::ReadString(&cis,obj.mPtrString ));
                                WireFormat::VerifyUTF8String((*obj.mPtrString).data(), (*obj.mPtrString).length(),WireFormat::PARSE);
                            }
                            if(cis.ExpectTag(56))
                            {
                                goto parse_mVecInt;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 7:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                        {
                            parse_mVecInt:
                            {
                                {
                                    auto v = InsertPlaceholder(obj.mVecInt);
                                    DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&v)));

                                    if (cis.ExpectTag(56)) goto parse_mVecInt;
                                }
                            }
                            if(cis.ExpectTag(64))
                            {
                                goto parse_mVecPtrInt;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 8:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                        {
                            parse_mVecPtrInt:
                            {
                                if(nullptr == obj.mVecPtrInt)
                                {
                                    obj.mVecPtrInt = SerializeCreate(*obj.mVecPtrInt);
                                }
                                {
                                    auto v = InsertPlaceholder(*obj.mVecPtrInt);
                                    DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&v)));

                                    if (cis.ExpectTag(64)) goto parse_mVecPtrInt;
                                }
                            }
                            if(cis.ExpectTag(72))
                            {
                                goto parse_mVecIntPtr;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 9:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                        {
                            parse_mVecIntPtr:
                            {
                                {
                                    auto v = InsertPlaceholder(obj.mVecIntPtr);
                                    DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,v)));

                                    if (cis.ExpectTag(72)) goto parse_mVecIntPtr;
                                }
                            }
                            if(cis.ExpectTag(80))
                            {
                                goto parse_mVecPtrIntPtr;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 10:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                        {
                            parse_mVecPtrIntPtr:
                            {
                                if(nullptr == obj.mVecPtrIntPtr)
                                {
                                    obj.mVecPtrIntPtr = SerializeCreate(*obj.mVecPtrIntPtr);
                                }
                                {
                                    auto v = InsertPlaceholder(*obj.mVecPtrIntPtr);
                                    DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,v)));

                                    if (cis.ExpectTag(80)) goto parse_mVecPtrIntPtr;
                                }
                            }
                            if(cis.ExpectTag(88))
                            {
                                goto parse_mNestPtr;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 11:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                        {
                            parse_mNestPtr:
                            {
                                if(nullptr == obj.mNestPtr)
                                {
                                    obj.mNestPtr = SerializeCreate(*obj.mNestPtr);
                                }
                                DO_((DeserializeUser(cis,*obj.mNestPtr)));
                            }
                            if(cis.ExpectAtEnd())
                            {
                                break;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                default:
                {
                    handle_uninterpreted:
                    if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_END_GROUP)
                    {
                        return true;
                    }
                }
            }
        }
        return true;
    }

    int ByteSizeInternal(const ::Derived& obj)
    {
        int totalSize = 0;
        {
            int base_size = ByteSizeInternal(static_cast<const ::Base1&>(obj));
            totalSize += base_size + WireFormatLite::UInt32Size((uint32)base_size);
        }
        totalSize += 1 + 8;
        {
            uint32 usize = (uint32)ByteSizeInternal(obj.mNest);
            totalSize += 1 + usize + WireFormatLite::UInt32Size(usize);
        }
        totalSize += 1 + WireFormatLite::StringSize(obj.mString);
        if(nullptr != obj.mPtrString)
        {
            totalSize += 1 + WireFormatLite::StringSize(*obj.mPtrString);
        }
        for(auto& v : obj.mVecInt)
        {
            totalSize += 1 + WireFormatLite::SInt32Size(v);
        }
        if(nullptr != obj.mVecPtrInt)
        {
            for(auto& v : *obj.mVecPtrInt)
            {
                totalSize += 1 + WireFormatLite::SInt32Size(v);
            }
        }
        for(auto& v : obj.mVecIntPtr)
        {
            if(nullptr != v)
            {
                totalSize += 1 + WireFormatLite::SInt32Size(*v);
            }
        }
        if(nullptr != obj.mVecPtrIntPtr)
        {
            for(auto& v : *obj.mVecPtrIntPtr)
            {
                if(nullptr != v)
                {
                    totalSize += 1 + WireFormatLite::SInt32Size(*v);
                }
            }
        }
        if(nullptr != obj.mNestPtr)
        {
            {
                uint32 usize = (uint32)ByteSizeInternal(*obj.mNestPtr);
                totalSize += 1 + usize + WireFormatLite::UInt32Size(usize);
            }
        }
        return totalSize;
    }


    uint8* Serialize2Array(uint8* target,::Derived::Nest& obj)
    {
        //serialize mIntValue
        target = WireFormatLite::WriteSInt32ToArray(1,obj.mIntValue,target);
        //serialize mDoubleValue
        target = WireFormatLite::WriteDoubleToArray(2,obj.mDoubleValue,target);
        return target;
    }

    bool Serialize2CodedStream(io::CodedOutputStream& cos,::Derived::Nest& obj)
    {
        WireFormatLite::WriteSInt32(1,obj.mIntValue,&cos);
        WireFormatLite::WriteDouble(2,obj.mDoubleValue,&cos);
        return true;
    }

    bool DeserializeInternal(io::CodedInputStream& cis,::Derived::Nest& obj)
    {
        ::google::protobuf::uint32 tag;
        while((tag = cis.ReadTag()) != 0)
        {
            switch(WireFormatLite::GetTagFieldNumber(tag))
            {
                case 1:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                        {
                            parse_mIntValue:
                            {
                                DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&obj.mIntValue)));
                            }
                            if(cis.ExpectTag(17))
                            {
                                goto parse_mDoubleValue;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                case 2:
                    {
                        if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_FIXED64)
                        {
                            parse_mDoubleValue:
                            {
                                DO_((WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(&cis,&obj.mDoubleValue)));
                            }
                            if(cis.ExpectAtEnd())
                            {
                                break;
                            }
                        }
                        else
                        {
                            goto handle_uninterpreted;
                        }
                    }
                    break;
                default:
                {
                    handle_uninterpreted:
                    if(WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_END_GROUP)
                    {
                        return true;
                    }
                }
            }
        }
        return true;
    }

    int ByteSizeInternal(const ::Derived::Nest& obj)
    {
        int totalSize = 0;
        totalSize += 1 + WireFormatLite::SInt32Size(obj.mIntValue);
        totalSize += 1 + 8;
        return totalSize;
    }


}
#undef DO_
#undef private
