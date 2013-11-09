#define private public
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
    uint8* Serialize2Array(uint8*,::Base1&);
    bool Serialize2CodedStream(io::CodedOutputStream&,::Base1&);
    bool DeserializeInternal(io::CodedInputStream&,::Base1&);
    int ByteSizeInternal(const ::Base1&);

    uint8* Serialize2Array(uint8*,::Derived&);
    bool Serialize2CodedStream(io::CodedOutputStream&,::Derived&);
    bool DeserializeInternal(io::CodedInputStream&,::Derived&);
    int ByteSizeInternal(const ::Derived&);

    uint8* Serialize2Array(uint8*,::Derived::Nest&);
    bool Serialize2CodedStream(io::CodedOutputStream&,::Derived::Nest&);
    bool DeserializeInternal(io::CodedInputStream&,::Derived::Nest&);
    int ByteSizeInternal(const ::Derived::Nest&);

    bool Serialize2CodedStream(CodedOutputStream& cos,::Base1& obj)
    {
        //serialize base members
        
        //serialize this members
        using namespace ::google::protobuf::internal;

        //serialize mIntValue
        WireFormatLite::WriteSInt32(1,obj.mIntValue,&cos);

        //serialize mDoubleValue
        WireFormatLite::WriteDouble(2,obj.mDoubleValue,&cos);
        obj.Base1::OnSerialized_();
    }
    
    uint8* Serialize2Array(uint8* target,::Base1&obj)
    {
        //serialize base members
        
        //serialize this members
        using namespace ::google::protobuf::internal;

        //serialize mIntValue
        target = WireFormatLite::WriteSInt32ToArray(1,obj.mIntValue,target);

        //serialize mDoubleValue
        target = WireFormatLite::WriteDoubleToArray(2,obj.mDoubleValue,target);
        obj.Base1::OnSerialized_();
        return target;
    }
    
    bool DeserializeInternal(CodedInputStream& cis,::Base1& obj)
    {
    #define DO_(EXPRESSION) if (!(EXPRESSION)) return false
        //deserialize base members
        ::google::protobuf::uint32 tag;
        while ((tag = cis.ReadTag()) != 0) 
        {
            switch (WireFormatLite::GetTagFieldNumber(tag))
            {
            //required sint32  mIntValue = 1[default:];
            case 1:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                    {
                    parse_mIntValue:
                        DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&obj.mIntValue)));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(17))
                    {
                        goto parse_mDoubleValue;
                    }
                }
                break;
            //optional double  mDoubleValue = 2[default:];
            case 2:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_FIXED64)
                    {
                    parse_mDoubleValue:
                        DO_((WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(&cis,&obj.mDoubleValue)));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectAtEnd()) return true;
                }
                break;
            default:
                {
                handle_uninterpreted:
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_END_GROUP)
                    {
                        return true;
                    }
                    break;
                }
            }//switch
        }//while
        return true;
        #undef DO_
    }

    int ByteSizeInternal(const ::Base1& obj)
    {
        int total_size = 0;
        total_size += 1 + WireFormatLite::SInt32Size(obj.mIntValue);
        total_size += 1 + 8;
        return total_size;
    }
    
    bool Serialize2CodedStream(CodedOutputStream& cos,::Derived& obj)
    {
        obj.Derived::OnSerializing();
        //serialize base members
        WireFormatLite::WriteUInt32NoTag((uint32)ByteSizeInternal(static_cast<::Base1&>(obj)),&cos);
        Serialize2CodedStream(cos,static_cast<::Base1&>(obj));
        
        //serialize this members
        using namespace ::google::protobuf::internal;

        //serialize mDValue
        WireFormatLite::WriteDouble(3,obj.mDValue,&cos);

        //serialize mNest
        {
            uint32 usize = (uint32)ByteSizeInternal(obj.mNest);
            WireFormatLite::WriteTag(4, WireFormatLite::WIRETYPE_LENGTH_DELIMITED, &cos);
            WireFormatLite::WriteUInt32NoTag(usize,&cos);
            Serialize2CodedStream(cos,obj.mNest);
        }

        //serialize mString
        WireFormatLite::WriteString(5,obj.mString,&cos);

        //serialize mPtrString
        if(nullptr != obj.mPtrString)
        {
            WireFormatLite::WriteString(6,*obj.mPtrString,&cos);
        }

        //serialize mVecInt
        for(auto it_child = std::begin(obj.mVecInt);it_child != std::end(obj.mVecInt);++it_child)
        {
            WireFormatLite::WriteSInt32(7,(*it_child),&cos);
        }

        //serialize mVecPtrInt
        for(auto it_child = std::begin(*obj.mVecPtrInt);it_child != std::end(*obj.mVecPtrInt);++it_child)
        {
            WireFormatLite::WriteSInt32(8,(*it_child),&cos);
        }

        //serialize mVecIntPtr
        for(auto it_child = std::begin(obj.mVecIntPtr);it_child != std::end(obj.mVecIntPtr);++it_child)
        {
            WireFormatLite::WriteSInt32(9,*(*it_child),&cos);
        }

        //serialize mVecPtrIntPtr
        for(auto it_child = std::begin(*obj.mVecPtrIntPtr);it_child != std::end(*obj.mVecPtrIntPtr);++it_child)
        {
            WireFormatLite::WriteSInt32(10,*(*it_child),&cos);
        }

        //serialize mNestPtr
        if(nullptr != obj.mNestPtr)
        {
            {
                uint32 usize = (uint32)ByteSizeInternal(*obj.mNestPtr);
                WireFormatLite::WriteTag(11, WireFormatLite::WIRETYPE_LENGTH_DELIMITED, &cos);
                WireFormatLite::WriteUInt32NoTag(usize,&cos);
                Serialize2CodedStream(cos,*obj.mNestPtr);
            }
        }
    }
    
    uint8* Serialize2Array(uint8* target,::Derived&obj)
    {
        obj.Derived::OnSerializing();
        //serialize base members
        target = WireFormatLite::WriteUInt32NoTagToArray((uint32)ByteSizeInternal(static_cast<::Base1&>(obj)),target);
        target = Serialize2Array(target,static_cast<::Base1&>(obj));
        
        //serialize this members
        using namespace ::google::protobuf::internal;

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
        for(auto it_child = std::begin(obj.mVecInt);it_child != std::end(obj.mVecInt);++it_child)
        {
            target = WireFormatLite::WriteSInt32ToArray(7,(*it_child),target);
        }

        //serialize mVecPtrInt
        for(auto it_child = std::begin(*obj.mVecPtrInt);it_child != std::end(*obj.mVecPtrInt);++it_child)
        {
            target = WireFormatLite::WriteSInt32ToArray(8,(*it_child),target);
        }

        //serialize mVecIntPtr
        for(auto it_child = std::begin(obj.mVecIntPtr);it_child != std::end(obj.mVecIntPtr);++it_child)
        {
            target = WireFormatLite::WriteSInt32ToArray(9,*(*it_child),target);
        }

        //serialize mVecPtrIntPtr
        for(auto it_child = std::begin(*obj.mVecPtrIntPtr);it_child != std::end(*obj.mVecPtrIntPtr);++it_child)
        {
            target = WireFormatLite::WriteSInt32ToArray(10,*(*it_child),target);
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
    
    bool DeserializeInternal(CodedInputStream& cis,::Derived& obj)
    {
    #define DO_(EXPRESSION) if (!(EXPRESSION)) return false
        //deserialize base members
        DeserializeUser(cis,static_cast<Base1&>(obj));
        ::google::protobuf::uint32 tag;
        while ((tag = cis.ReadTag()) != 0) 
        {
            switch (WireFormatLite::GetTagFieldNumber(tag))
            {
            //optional double  mDValue = 3[default:];
            case 3:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_FIXED64)
                    {
                    parse_mDValue:
                        DO_((WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(&cis,&obj.mDValue)));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(34))
                    {
                        goto parse_mNest;
                    }
                }
                break;
            //required Nest mNest = 4[default:];
            case 4:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                    {
                    parse_mNest:
                        DO_((DeserializeUser(cis,obj.mNest)));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(42))
                    {
                        goto parse_mString;
                    }
                }
                break;
            //required string  mString = 5[default:];
            case 5:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                    {
                    parse_mString:
                        DO_(WireFormatLite::ReadString(&cis,&obj.mString ));
                        WireFormat::VerifyUTF8String(obj.mString.data(), obj.mString.length(),WireFormat::PARSE);
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(50))
                    {
                        goto parse_mPtrString;
                    }
                }
                break;
            //required string *  mPtrString = 6[default:];
            case 6:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                    {
                    parse_mPtrString:
                        if(nullptr == obj.mPtrString)
                        {
                            obj.mPtrString = SerializeCreate(*obj.mPtrString);
                        }
                        DO_(WireFormatLite::ReadString(&cis,obj.mPtrString ));
                        WireFormat::VerifyUTF8String(obj.mPtrString->data(), obj.mPtrString->length(),WireFormat::PARSE);
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(56))
                    {
                        goto parse_mVecInt;
                    }
                }
                break;
            //required array<sint32 >  mVecInt = 7[default:];
            case 7:
                {
                    if (WireFormatLite::GetTagWireType(tag) == 0)
                    {
                    parse_mVecInt:
                        DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&InsertPlaceholder(obj.mVecInt))));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(56)) goto parse_mVecInt;
                    if (cis.ExpectTag(64))
                    {
                        goto parse_mVecPtrInt;
                    }
                }
                break;
            //required array<sint32 > *  mVecPtrInt = 8[default:];
            case 8:
                {
                    if (WireFormatLite::GetTagWireType(tag) == 0)
                    {
                    parse_mVecPtrInt:
                        if(nullptr == obj.mVecPtrInt)
                        {
                            obj.mVecPtrInt = SerializeCreate(*obj.mVecPtrInt);
                        }
                        DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&InsertPlaceholder(*obj.mVecPtrInt))));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(64)) goto parse_mVecPtrInt;
                    if (cis.ExpectTag(72))
                    {
                        goto parse_mVecIntPtr;
                    }
                }
                break;
            //required array<sint32 * >  mVecIntPtr = 9[default:];
            case 9:
                {
                    if (WireFormatLite::GetTagWireType(tag) == 0)
                    {
                    parse_mVecIntPtr:
                        DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,InsertPlaceholder(obj.mVecIntPtr))));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(72)) goto parse_mVecIntPtr;
                    if (cis.ExpectTag(80))
                    {
                        goto parse_mVecPtrIntPtr;
                    }
                }
                break;
            //required array<sint32 * > *  mVecPtrIntPtr = 10[default:];
            case 10:
                {
                    if (WireFormatLite::GetTagWireType(tag) == 0)
                    {
                    parse_mVecPtrIntPtr:
                        if(nullptr == obj.mVecPtrIntPtr)
                        {
                            obj.mVecPtrIntPtr = SerializeCreate(*obj.mVecPtrIntPtr);
                        }
                        DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,InsertPlaceholder(*obj.mVecPtrIntPtr))));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(80)) goto parse_mVecPtrIntPtr;
                    if (cis.ExpectTag(90))
                    {
                        goto parse_mNestPtr;
                    }
                }
                break;
            //required Nest*  mNestPtr = 11[default:];
            case 11:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
                    {
                    parse_mNestPtr:
                        if(nullptr == obj.mNestPtr)
                        {
                            obj.mNestPtr = SerializeCreate(*obj.mNestPtr);
                        }
                        DO_((DeserializeUser(cis,*obj.mNestPtr)));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectAtEnd()) return true;
                }
                break;
            default:
                {
                handle_uninterpreted:
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_END_GROUP)
                    {
                        return true;
                    }
                    break;
                }
            }//switch
        }//while
        return true;
        #undef DO_
    }

    int ByteSizeInternal(const ::Derived& obj)
    {
        int total_size = 0;
        {
            int base_size = ByteSizeInternal(static_cast<const Base1&>(obj));
            total_size += base_size + WireFormatLite::UInt32Size((uint32)base_size);
        }
        total_size += 1 + 8;
        {
            uint32 usize = (uint32)ByteSizeInternal(obj.mNest);
            total_size += 1 + ByteSizeInternal(obj.mNest);
            total_size += WireFormatLite::UInt32Size(usize);
        }
        total_size += 1 + WireFormatLite::StringSize(obj.mString);
        if(nullptr != obj.mPtrString)
        {
            total_size += 1 + WireFormatLite::StringSize(*obj.mPtrString);
        }
        for(auto& v : obj.mVecInt)
        {
            total_size += 1 + WireFormatLite::SInt32Size(v);

        }
        if(nullptr != obj.mVecPtrInt)
        {
            for(auto& v : *obj.mVecPtrInt)
            {
                total_size += 1 + WireFormatLite::SInt32Size(v);

            }
        }
        for(auto& v : obj.mVecIntPtr)
        {
            total_size += 1 + WireFormatLite::SInt32Size(*v);

        }
        if(nullptr != obj.mVecPtrIntPtr)
        {
            for(auto& v : *obj.mVecPtrIntPtr)
            {
                total_size += 1 + WireFormatLite::SInt32Size(*v);

            }
        }
        if(nullptr != obj.mNestPtr)
        {
            {
                uint32 usize = (uint32)ByteSizeInternal(*obj.mNestPtr);
                total_size += 1 + ByteSizeInternal(*obj.mNestPtr);
                total_size += WireFormatLite::UInt32Size(usize);
            }
        }
        return total_size;
    }
    
    bool Serialize2CodedStream(CodedOutputStream& cos,::Derived::Nest& obj)
    {
        //serialize base members
        
        //serialize this members
        using namespace ::google::protobuf::internal;

        //serialize mIntValue
        WireFormatLite::WriteSInt32(1,obj.mIntValue,&cos);

        //serialize mDoubleValue
        WireFormatLite::WriteDouble(2,obj.mDoubleValue,&cos);
    }
    
    uint8* Serialize2Array(uint8* target,::Derived::Nest&obj)
    {
        //serialize base members
        
        //serialize this members
        using namespace ::google::protobuf::internal;

        //serialize mIntValue
        target = WireFormatLite::WriteSInt32ToArray(1,obj.mIntValue,target);

        //serialize mDoubleValue
        target = WireFormatLite::WriteDoubleToArray(2,obj.mDoubleValue,target);
        return target;
    }
    
    bool DeserializeInternal(CodedInputStream& cis,::Derived::Nest& obj)
    {
    #define DO_(EXPRESSION) if (!(EXPRESSION)) return false
        //deserialize base members
        ::google::protobuf::uint32 tag;
        while ((tag = cis.ReadTag()) != 0) 
        {
            switch (WireFormatLite::GetTagFieldNumber(tag))
            {
            //required sint32  mIntValue = 1[default:];
            case 1:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_VARINT)
                    {
                    parse_mIntValue:
                        DO_((WireFormatLite::ReadPrimitive<int32, WireFormatLite::TYPE_SINT32>(&cis,&obj.mIntValue)));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectTag(17))
                    {
                        goto parse_mDoubleValue;
                    }
                }
                break;
            //optional double  mDoubleValue = 2[default:];
            case 2:
                {
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_FIXED64)
                    {
                    parse_mDoubleValue:
                        DO_((WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(&cis,&obj.mDoubleValue)));
                    }
                    else
                    {
                        goto handle_uninterpreted;
                    }
                    if (cis.ExpectAtEnd()) return true;
                }
                break;
            default:
                {
                handle_uninterpreted:
                    if (WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_END_GROUP)
                    {
                        return true;
                    }
                    break;
                }
            }//switch
        }//while
        return true;
        #undef DO_
    }

    int ByteSizeInternal(const ::Derived::Nest& obj)
    {
        int total_size = 0;
        total_size += 1 + WireFormatLite::SInt32Size(obj.mIntValue);
        total_size += 1 + 8;
        return total_size;
    }
    
}
#undef private
