#ifndef _SE_FIELDBUILDER_H
#define _SE_FIELDBUILDER_H 
#include "IField.h"
#include "FieldType.h"
class FieldBuilder
{
public:
    IField::Ptr BuildField(FieldType t,const std::string& name,int seqNo);          //like : int 
    IField::Ptr BuildPtr(FieldType t,const std::string& name,int seqNo);            //like : int* 
    IField::Ptr BuildArray(FieldType t,const std::string& name,int seqNo);          //like : vector<int>
    IField::Ptr BuildArrayPtr(FieldType t,const std::string& name,int seqNo);       //like : vecotr<int>*
    IField::Ptr BuildPtrArray(FieldType t,const std::string& name,int seqNo);       //like : vector<int*> 
    IField::Ptr BuildPtrArrayPtr(FieldType t,const std::string& name,int seqNo);    //like : vector<int*>* 
};
#endif

