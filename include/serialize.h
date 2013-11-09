#ifndef _PROTO_SERIALIZE_H
#define _PROTO_SERIALIZE_H
#include <string>
#include <stdint.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/wire_format_lite.h>
namespace Serialization
{
using namespace std;
using namespace google::protobuf;
typedef uint8_t uint8;
inline char* string_as_array(const string& str)
{ 
   // DO NOT USE const_cast<char*>(str->data())! See the unittest for why.
   return str.empty() ? NULL : const_cast<char*>(&*str.begin());
}  

inline void ByteSizeConsistencyError(int byte_size_before_serialization,                                                                                                               
                              int byte_size_after_serialization,                                                                                                                
                              int bytes_produced_by_serialization) 
{
  GOOGLE_CHECK_EQ(byte_size_before_serialization, byte_size_after_serialization)
      << "Protocol message was modified concurrently during serialization.";
  GOOGLE_CHECK_EQ(bytes_produced_by_serialization, byte_size_before_serialization)
      << "Byte size calculation and serialization were inconsistent.  This "
         "may indicate a bug in protocol buffers or it may be caused by "
         "concurrent modification of the message.";
  GOOGLE_LOG(FATAL) << "This shouldn't be called if all the sizes are equal.";
}    

//======Serialize single object===========================================
template<typename T>
int ByteSize(const T& obj)
{
    int ByteSizeInternal(const T&);
    return ByteSizeInternal(obj);
}

template<typename T>
bool Serialize(std::ostream& output,T& obj)
{
    uint8* Serialize2Array(uint8*,T&);
    bool Serialize2CodedStream(io::CodedOutputStream&,T&);

    io::OstreamOutputStream zero_copy_output(&output);
    io::CodedOutputStream encoder(&zero_copy_output);
    const int size = ByteSize(obj);  // Force size to be cached.     

    uint8* buffer = encoder.GetDirectBufferForNBytesAndAdvance(size); 
    if (buffer != NULL)
    {
	uint8* end = Serialize2Array(buffer,obj);
	if (end - buffer != size)
	{
	    ByteSizeConsistencyError(size, ByteSize(obj), end - buffer);
	}
	return true;
    }
    else 
    {
	int original_byte_count = encoder.ByteCount();
	Serialize2CodedStream(encoder,obj);
	if (encoder.HadError()) 
	{
	    return false;
	}
	int final_byte_count = encoder.ByteCount();

	if (final_byte_count - original_byte_count != size)
	{
	    ByteSizeConsistencyError(size, ByteSize(obj),final_byte_count - original_byte_count);
	}

	return true;                                                                                                                                                                
    }  
}

template<typename T>
bool Serialize(std::string& output,const T& obj)
{
    bool Serialize2Array(uint8*,T&);
    output.clear();

    int byte_size = ByteSize(obj);
    uint8* start = reinterpret_cast<uint8*>(string_as_array(output));
    uint8* end = Serialize2Array(start,obj);
    if (end - start != byte_size)
    {
	ByteSizeConsistencyError(byte_size, ByteSize(obj), end - start);
    }
}


template<typename T>
bool Serialize(void* output,int size,const T& obj)
{
    bool Serialize2Array(uint8*,T&);
    int byte_size = ByteSize(obj); 
    if (size < byte_size) return false;

    uint8* start = reinterpret_cast<uint8*>(output);
    uint8* end = Serialize2Array(start);
    if (end - start != byte_size) 
    {
	ByteSizeConsistencyError(byte_size, ByteSize(obj), end - start);
    }
    return true; 
}

template<typename T>
bool Deserialize(std::istream& input,T& obj)
{
    bool DeserializeInternal(io::CodedInputStream&,T&);

    io::IstreamInputStream zero_copy_input(&input);
    io::CodedInputStream decoder(&zero_copy_input);
    
    return DeserializeInternal(decoder,obj);
}

template<typename T>
bool Deserialize(const void* data,int size,T& obj)
{
    bool DeserializeInternal(io::CodedInputStream&,T&);
    io::CodedInputStream decoder(reinterpret_cast<const uint8*>(data),size);

    return DeserializeInternal(decoder,obj);
}

template<typename T>
bool Deserialize(const std::string& input,T& obj)
{
    return Deserialize(input.data(),input.size(),obj);
}

template<typename T>
bool DeserializeUser(io::CodedInputStream& input,T& obj)
{
    uint32 length;
    if (!input.ReadVarint32(&length)) return false;
    if (!input.IncrementRecursionDepth()) return false;
    io::CodedInputStream::Limit limit = input.PushLimit(length);

    bool DeserializeInternal(io::CodedInputStream&,T&);
    if(!DeserializeInternal(input,obj)) return false;

    // Make sure that parsing stopped when the limit was hit, not at an endgroup
    // tag.
    if (!input.ConsumedEntireMessage()) return false;
    input.PopLimit(limit);
    input.DecrementRecursionDepth();
    return true;
}
    
    
      //=======Serialize array=====================================================
template<typename Iterator>
bool Serialize(io::CodedOutputStream& cos,Iterator begin,Iterator end,size_t size)
{
    cos.WriteVarint32(size);
    for(int saved = 0; saved < size && begin != end;++begin,++saved)
    {
	if(nullptr != begin)
	{
	    Serialize(cos,*begin);
	}
    }
    return true;
}

template<typename Iterator>
bool Serialize(std::ostream& os,Iterator begin,Iterator end,size_t size)
{
    io::CodedOutputStream cos(os);
    return Serialize(os,begin,end,size);
}


template<typename InsertIterator>
bool Deserialize(io::CodedInputStream& cis,InsertIterator insertor)
{
    uint32_t size;
    cis.ReadVarint32(&size);
    while(size > 0)
    {
	Deserialize(cis,*insertor);
	--size;
    }

    return true;
}

//template<typename InsertIterator>
//bool Deserialize(std::istream& is,InsertIterator insertor)
//{
//    io::CodedInputStream cis(is);
//    return Deserialize(cis,insertor);
//}
}
#endif
 
