#include "Class.h"
#include "FormatStream.h"
#include "GuardAble.h"
Class::Class(const std::string& name)
    :mName(name)
    ,mSerialize2ArrayDeclare("uint8* Serialize2Array(uint8* target," + mName + "& obj)")
    ,mSerialize2CodedStreamDeclare("bool Serialize2CodedStream(io::CodedOutputStream& cos," + mName + "& obj)")
    ,mDeserializeDeclare("bool DeserializeInternal(io::CodedInputStream& cis," + mName + "& obj)")
    ,mByteSizeDeclare("int ByteSizeInternal(const " + mName + "& obj)")
    ,mCallbacks(0)
{
}
void Class::CodingDeclare(FormatStream& fos)const
{
    //fos<<"class " + mName<<";"<<std::endl;
    fos<<mSerialize2ArrayDeclare<<";"<<std::endl;
    fos<<mSerialize2CodedStreamDeclare<<";"<<std::endl;
    fos<<mDeserializeDeclare<<";"<<std::endl;
    fos<<mByteSizeDeclare<<";"<<std::endl<<std::endl;
}

void Class::Coding(FormatStream& fos) const
{
    auto itPrev = Fields().rbegin();
    for(auto itField = Fields().rbegin() + 1; itField != Fields().rend(); ++itField)
    {
	(*itField)->SetNext(*itPrev);
	itPrev = itField;
    }
    CodingSerialize2Array(fos);
    CodingSerialize2CodedStream(fos);
    CodingDeserialize(fos);
    CodingByteSize(fos);
    fos.BaseStream()<<std::endl;
}

void Class::CodingSerialize2Array(FormatStream& fos) const
{
    BLOCK_EX(fos,mSerialize2ArrayDeclare)
    {
	PreSerialize(fos);
    	for(auto& pBase : Bases())
	{
	   fos<<"target = WireFormatLite::WriteUInt32NoTagToArray((uint32)ByteSizeInternal(static_cast<"<<pBase->Name()<<"&>(obj)),target);"<<std::endl;
	   fos<<"target = Serialize2Array(target,static_cast<"<<pBase->Name()<<"&>(obj));"<<std::endl;
	}

	for(auto& pField : Fields())
	{
	    fos<<"//serialize "<<pField->Name()<<std::endl;
	    pField->CodingSerialize2Array(fos);
	}

	PostSerialize(fos);
	fos<<"return target;"<<std::endl;
    }
    fos.BaseStream()<<std::endl;
}

void Class::CodingSerialize2CodedStream(FormatStream& fos) const
{
    BLOCK_EX(fos,mSerialize2CodedStreamDeclare)
    {
	PreSerialize(fos);

	for(auto& pBase : Bases())
	{
	   fos<<"WireFormatLite::WriteUInt32NoTag((uint32)ByteSizeInternal(static_cast<"<<pBase->Name()<<"&>(obj)),&cos);"<<std::endl;
	   fos<<"Serialize2CodedStream(cos,static_cast<"<<pBase->Name()<<"&>(obj));"<<std::endl;
	}

	for(auto& pField : Fields())
	{
	    pField->CodingSerialize2CodedStream(fos);
	}

	PostSerialize(fos);
	fos<<"return true;"<<std::endl;
    }
    fos.BaseStream()<<std::endl;
}

void Class::CodingDeserialize(FormatStream& fos) const
{
    BLOCK_EX(fos,mDeserializeDeclare)
    {
	PreDeSerialize(fos);

	for(auto& pBase : Bases())
	{
            fos<<"DeserializeUser(cis,static_cast<"<<pBase->Name()<<"&>(obj));"<<std::endl;
	}
        //deserialize base members
        fos<<"::google::protobuf::uint32 tag;"<<std::endl;
	WHILE(fos,"(tag = cis.ReadTag()) != 0")
	{
	    SWITCH(fos,"WireFormatLite::GetTagFieldNumber(tag)")
	    {
		for(auto& pField : Fields())
		{
		    pField->CodingDeserialize(fos);
		}

		DEFAULT(fos)
		{
		    fos<<"handle_uninterpreted:"<<std::endl;
		    IF(fos,"WireFormatLite::GetTagWireType(tag) == WireFormatLite::WIRETYPE_END_GROUP")
		    {
			fos<<"return true;"<<std::endl;
		    }
	        }
	    }
	}

	PostDeSerialize(fos);

	fos<<"return true;"<<std::endl;
    }
    fos.BaseStream()<<std::endl;
}

void Class::CodingByteSize(FormatStream& fos) const
{
    BLOCK_EX(fos,mByteSizeDeclare)
    {
	fos<<"int totalSize = 0;"<<std::endl;
	for(auto& pBase : Bases())
	{
	    BLOCK(fos)
	    {
		fos<<"int base_size = ByteSizeInternal(static_cast<const "<<pBase->Name()<<"&>(obj));"<<std::endl;
		fos<<"totalSize += base_size + WireFormatLite::UInt32Size((uint32)base_size);"<<std::endl;
	    }
	}

    	for(auto& pField : Fields())
	{
	    pField->CodingByteSize(fos);
	}
	fos<<"return totalSize;"<<std::endl;
    }
    fos.BaseStream()<<std::endl;
}

void Class::SetCallback(SerializeCallback callback,const std::string& name)
{
    mCallbacks |= callback;
    
    switch(callback)
    {
	case SEC_ONSERIALIZING:
	    mCallbackNames[0] = name;
	case SEC_ONSERIALIZED:
	    mCallbackNames[1] = name;
	case SEC_ONDESERIALIZEING:
	    mCallbackNames[2] = name;
	default:
	    mCallbackNames[3] = name;
    }
}

const std::string& Class::GetCallbackName(SerializeCallback callback) const
{
    switch(callback)
    {
	case SEC_ONSERIALIZING:
	    return mCallbackNames[0];
	case SEC_ONSERIALIZED:
	    return mCallbackNames[1];
	case SEC_ONDESERIALIZEING:
	    return mCallbackNames[2];
	default:
	    return mCallbackNames[3];
    }
}

void Class::PreSerialize(FormatStream& fos) const
{
    if(HasSerializing())
    {
	fos<<"obj."<<Name()<<"::"<<GetCallbackName(SEC_ONSERIALIZING)<<"();"<<std::endl;
    }
}

void Class::PostSerialize(FormatStream& fos) const
{
    if(HasSerialized())
    {
	fos<<"obj."<<Name()<<"::"<<GetCallbackName(SEC_ONSERIALIZED)<<"();"<<std::endl;
    }
}

void Class::PreDeSerialize(FormatStream& fos) const
{
    if(HasDeserializing())
    {
	fos<<"obj."<<Name()<<"::"<<GetCallbackName(SEC_ONDESERIALIZEING)<<"();"<<std::endl;
    }
}

void Class::PostDeSerialize(FormatStream& fos ) const
{
    if(HasDeserialized())
    {
	fos<<"obj."<<Name()<<"::"<<GetCallbackName(SEC_ONDESERIALIZED)<<"();"<<std::endl;
    }
}
