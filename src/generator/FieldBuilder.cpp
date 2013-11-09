#include <stdexcept>
#include "FieldBuilder.h"
#include "BoolField.h"
#include "UIntField.h"
#include "PointerDecorator.h"
#include "ArrayDecorator.h"
#include "SIntField.h"
#include "StringField.h"
#include "FloatField.h"
#include "DoubleField.h"
#include "EnumField.h"
#include "ClassField.h"
IField::Ptr FieldBuilder::BuildField(FieldType t,const std::string& name,int seqNo)          //like : int 
{
    IField::Ptr newField;
    switch(t)
    {
        case EN_BOOL_FIELD:
	    newField.reset(new BoolField(name,seqNo));
	    break;
        case EN_UINT8_FIELD:
	    newField.reset(new UIntField(name,8,seqNo));
	    break;
        case EN_UINT16_FIELD:
	    newField.reset(new UIntField(name,16,seqNo));
	    break;
        case EN_UINT32_FIELD:
	    newField.reset(new UIntField(name,32,seqNo));
            break;
        case EN_UINT64_FIELD:
	    newField.reset(new UIntField(name,64,seqNo));
	    break;
        case EN_SINT8_FIELD:
	    newField.reset(new SIntField(name,8,seqNo));
	    break;
        case EN_SINT16_FIELD:
	    newField.reset(new SIntField(name,16,seqNo));
            break;
        case EN_SINT32_FIELD:
	    newField.reset(new SIntField(name,32,seqNo));
	    break;
        case EN_SINT64_FIELD:
	    newField.reset(new SIntField(name,64,seqNo));
	    break;
        case EN_FLOAT_FIELD:
	    newField.reset(new FloatField(name,seqNo));
	    break;
        case EN_DOUBLE_FIELD:
	    newField.reset(new DoubleField(name,seqNo));
	    break;
        case EN_ENUM_FIELD:
	    newField.reset(new EnumField(name,seqNo));
	    break;
        case EN_STRING_FIELD:
	    newField.reset(new StringField(name,seqNo));
	    break;
        case EN_USER_FIELD:
	    newField.reset(new ClassField(name,seqNo));
	    break;
	default:
	    throw std::logic_error("can't create composite type using this function.");
    }
    newField->Initialize();
    return newField;
}

IField::Ptr FieldBuilder::BuildPtr(FieldType t,const std::string& name,int seqNo)            //like : int* 
{
    IField::Ptr decoratedField = BuildField(t,name,seqNo);
    IField::Ptr ptrField(new PointerDecorator(decoratedField));
    ptrField->Initialize();
    return ptrField;
}

IField::Ptr FieldBuilder::BuildArray(FieldType t,const std::string& name,int seqNo)          //like : vector<int>
{
    IField::Ptr decoratedField = BuildField(t,"v",seqNo);
    IField::Ptr arrayField(new ArrayDecorator(name,decoratedField));
    decoratedField->QNameSameAsName();
    arrayField->Initialize();
    return arrayField;
}

IField::Ptr FieldBuilder::BuildArrayPtr(FieldType t,const std::string& name,int seqNo)       //like : vecotr<int>*
{
    IField::Ptr decoratedField = BuildField(t,"v",seqNo);
    IField::Ptr arrayField(new ArrayDecorator(name,decoratedField));
    IField::Ptr arrayPtr(new PointerDecorator(arrayField));
    decoratedField->QNameSameAsName();
    arrayField->Initialize();
    arrayPtr->Initialize();
    return arrayPtr;
}

IField::Ptr FieldBuilder::BuildPtrArray(FieldType t,const std::string& name,int seqNo)       //like : vector<int*> 
{
    IField::Ptr decoratedField = BuildField(t,"v",seqNo);
    PointerDecorator::Ptr ptrField(new PointerDecorator(decoratedField));
    IField::Ptr ptrArray(new ArrayDecorator(name,ptrField));
    decoratedField->QNameSameAsName();
    ptrField->CreateIfNull(false);
    ptrField->Initialize();
    ptrArray->Initialize();
    return ptrArray;
}

IField::Ptr FieldBuilder::BuildPtrArrayPtr(FieldType t,const std::string& name,int seqNo)    //like : vector<int*>* 
{
    IField::Ptr decoratedField = BuildField(t,"v",seqNo);
    PointerDecorator::Ptr ptrField(new PointerDecorator(decoratedField));
    IField::Ptr arrayField(new ArrayDecorator(name,ptrField));
    IField::Ptr ptr(new PointerDecorator(arrayField));
    decoratedField->QNameSameAsName();
    ptrField->CreateIfNull(false);
    ptrField->Initialize();
    arrayField->Initialize();
    ptr->Initialize();
    return ptr;
}


