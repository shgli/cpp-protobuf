#ifndef _SE_DEFAULTVALUE_H
#define _SE_DEFAULTVALUE_H
#include "gcc.h"
#include <string>
struct DefaultValue                                                                                                                                                                               
{                                                                                                                                                                                                  
  enum enKindType                                                                                                                                                                                   
  {                                                                                                                                                                                                
    EN_Reset,   // Default value reset.                                                                                                                                                               
    EN_Null,                                                                                                                                                                                          
    EN_Boolean,  // Literal contains value (true or false).                                                                                                                                           
    EN_Integer,  // Integer number. Literal contains sign.                                                                                                                                            
    EN_Floating, // Floating-point number.                                                                                                                                                            
    EN_String,   // Literal contains value.                                                                                                                                                           
    EN_Enumerator // Literal is the name, enum_value is the tree node.                                                                                                                                
  };                                                                                                                                                                                               
                                                                                                                                                                                                   
  enKindType Kind;                                                                                                                                                                                  
  std::string Literal;                                                                                                                                                                             
                                                                                                                                                                                                   
  union                                                                                                                                                                                            
  {                                                                                                                                                                                                
    tree EnumValue;                                                                                                                                                                               
    unsigned long long IntValue;                                                                                                                                                                  
    double FloatValue;                                                                                                                                                                            
  };                                                                                                                                                                                               
};  
#endif

