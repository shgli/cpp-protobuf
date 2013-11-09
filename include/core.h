#ifndef _CPP_PROTOBUF_H
#define _CPP_PROTOBUF_H

#ifdef CPP_PROTOBUF_COMPILER
    #define PRAGMA                     #pragma
    #define Serializable               #pragma protobuf serializable
    #define Required(seq,dval)         PRAGMA protobuf field required dval seq
    #define Optional(seq,dval)         PRAGMA protobuf field optional dval seq
    #define Repeated(seq,dval)         PRAGMA protobuf field repeated dval seq
    #define OnSerialized               #pragma protobuf method onserialized
    #define OnSerializing              #pragma protobuf method onserializing
    #define OnDeserialized             #pragma protobuf method ondeserialized
    #define OnDeserializing            #pragma protobuf method ondeserializing
#else
    #define Serializable               
    #define Required
    #define Optional
    #define Repeated
    #define OnSerialized               
    #define OnSerializing              
    #define OnDeserialized             
    #define OnDeserializing            
#endif//CPP_PROTOBUF_COMPILER

#endif//_CPP_PROTOBUF_H

