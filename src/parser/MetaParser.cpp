#include "gcc.h"
#include <cctype> // std::isalnum
#include <limits>                                                                                                                                                                                  
#include <vector>
#include <sstream>   
#include <iostream>
#include <sstream>
#include <limits>
#include "diagnostics.h"
#include "MetaParser.h"
#include "CppLexer.h"
void MetaParser::Parse( void )
{
  cxx_pragma_lexer l;
  l.start ();

  std::string tl;
  cpp_ttype tt (l.next (tl));

  if(0 == Compare(tl,"serializable"))
  {
      ParseSerializable(l);
  }
  else if(0 == Compare(tl,"field"))
  {
      ParseFieldMeta(l);
  }
  else if(0 == Compare(tl,"method"))
  {
      ParseMethodMeta(l);
  }
  else
  {
      error(l) << "after pragma protobuf shoud be one of these selectors : serializable,field and method" <<std::endl;
      exit(1);
  }
}

void MetaParser::ParseSerializable(cxx_pragma_lexer& l)
{
    std::string t;
    if(CPP_EOF != l.next(t))
    {
	warn(l) << "nothing should be appeared after selector 'serializable'"<<std::endl;
    }
    else
    {
	AddMeta(new Serializable(l.location()));
    }
}

void MetaParser::ParseFieldMeta(cxx_pragma_lexer& l)
{
    std::string tl;
    cpp_ttype type = l.next(tl);

    if(CPP_NAME == type)
    {
	SerializeField::enFieldRule ftype = SerializeField::EN_MaxRule;
	for(int i = 0; i < SerializeField::EN_MaxRule;++i)
	{
	    if(0 == Compare(tl,SerializeField::FieldTypeSpelling[i]))
	    {
		ftype = (SerializeField::enFieldRule)i;
		break;
	    }
	}

	if(SerializeField::EN_MaxRule != ftype)
	{
	    tree node;
	    type = l.next(tl,&node);
            DefaultValue dv; 
	    if(CPP_EQ == type)
	    {
		dv = ParseDefaultValue(l,type,tl,node);
	    }

            if(CPP_NUMBER == type)
	    {
		int seqno = 0;
		if(INTEGER_CST == TREE_CODE(node))
		{
		     HOST_WIDE_INT hwl (TREE_INT_CST_LOW (node));                                                                                                                                             
		     HOST_WIDE_INT hwh (TREE_INT_CST_HIGH (node));                                                                                                                                            
																									    
		     unsigned long long low (hwl);                                                                                                                                                            
		     unsigned long long high (hwh);                                                                                                                                                            
		     unsigned short width (HOST_BITS_PER_WIDE_INT);   
                     seqno = (high << width) + low;   
	             AddMeta(new SerializeField(l.location(),ftype,dv,seqno));
		}
		return;
	    }

	    error(l) << "s sequence number expected, but encounted "<<tl<<std::endl;
	    exit(1);
	}
    }

    error(l) << " after selector 'field',on of the following token expected: required,optional,repeated "<<std::endl;
}

DefaultValue MetaParser::ParseDefaultValue(cxx_pragma_lexer& l,cpp_ttype& tt,std::string& tl,tree& tn)
{
    DefaultValue dv;
    switch(l.next(tl,&tn))
    {
	case CPP_STRING:                                
	    {                                            
		dv.Kind = DefaultValue::EN_String;          
		dv.Literal = tl;                           
		tt = l.next (tl, &tn);                      
		break;                                       
	    }                                                 
	case CPP_NAME:                                         
	    {                                                   
		// This can be null or an enumerator name.       
		//                                                
		if (tl == "null")                                  
		{                                                   
		    dv.Kind = DefaultValue::EN_Null;                   
		    tt = l.next (tl, &tn);                            
		    break;                                             
		}                                                       
		else
		{
		    error(l) << "only number, string and enum can set default value"<<std::endl;
		    exit(1);
		}
		// Fall throught.                                        
	    }                                                                                                                                                                                            
	case CPP_SCOPE:                                                   
	    {                                                              
		//TODO:
		// We have a potentially scopped enumerator name.           
		//                                                           
		//dv.enum_value = resolve_scoped_name (                       
		//	l, tt, tl, tn, current_scope (), dv.literal, false, p);

		//if (dv.enum_value == 0)                           
		//    return; // Diagnostics has already been issued.

		tt = l.next(tl,&tn);
		dv.Kind = DefaultValue::EN_Enumerator;
		break;                      
	    }                                
	case CPP_MINUS:                       
	case CPP_PLUS:                         
	    {                                   
		if (tt == CPP_MINUS)             
		    dv.Literal = "-";

		tt = l.next (tl, &tn);             

		if (tt != CPP_NUMBER)                              
		{                                                   
		    error (l) << "expected numeric constant after '" 
			<< (tt == CPP_MINUS ? "-" : "+") << "' in protobuf default value" 
			<<std::endl;
		    exit(1);
		}                                                  

		// Fall through.                                    
	    }                                                        
	case CPP_NUMBER:                                              
	    {                                                          
		///////                                                 
		switch (TREE_CODE (tn))                                  
		{                                                         
		    case INTEGER_CST:                                      
			{                                                   
			    HOST_WIDE_INT hwl (TREE_INT_CST_LOW (tn));       
			    HOST_WIDE_INT hwh (TREE_INT_CST_HIGH (tn));       

			    unsigned long long l (hwl);                        
			    unsigned long long h (hwh);                         
			    unsigned short width (HOST_BITS_PER_WIDE_INT);       

			    dv.IntValue = (h << width) + l;                      
			    dv.Kind = DefaultValue::EN_Integer;                      
			    break;                                                  
			}                                                            
		    case REAL_CST:                                                    
			{                                                              
			    REAL_VALUE_TYPE d (TREE_REAL_CST (tn));                     

			    if (REAL_VALUE_ISINF (d))                                    
				dv.FloatValue = std::numeric_limits<double>::infinity ();
			    else if (REAL_VALUE_ISNAN (d))                                
				dv.FloatValue = std::numeric_limits<double>::quiet_NaN ();
			    else            
			    {                
				char tmp[256];
				real_to_decimal (tmp, &d, sizeof (tmp), 0, true);
				std::istringstream is (tmp); 
				is >> dv.FloatValue;         
			    }                                  

			    if (dv.Literal == "-")              
				dv.FloatValue = -dv.FloatValue;

			    dv.Kind = DefaultValue::EN_Floating;
			    break;
			}  
		    default:
			{  
			    error (l) << "unexpected numeric constant in protobuf pragma " << endl;
			    exit(1);
			}                                                                                                                                                                                        
		}                                                                                                                                                                                          

		tt = l.next (tl, &tn);                                                                                                                                                                     
		break;                                                                                                                                                                                     
	    }                                                                                                                                                                                            
	default:                                                                                                                                                                                       
	    {                                                                                                                                                                                            
		// This can be the true or false keyword.                                                                                                                                                  
		//                                                                                                                                                                                         
		if (tt == CPP_KEYWORD && (tl == "true" || tl == "false"))                                                                                                                                  
		{                                                                                                                                                                                          
		    dv.Kind = DefaultValue::EN_Boolean;                                                                                                                                                        
		    dv.Literal = tl;                                                                                                                                                                         
		    tt = l.next (tl, &tn);     
		}
		else                                                                                                                                                                                       
		{                                                                                                                                                                                          
		    error (l) << "unexpected expression in protobuf pragma " << endl;                                                                                                                         
		    exit(1);
		}                                                                                                                                                                                          

		break;                                                                                                                                                                                     
	    }         
    }
    return dv;
}

void MetaParser::ParseMethodMeta(cxx_pragma_lexer& l)
{
    std::string tl;
    cpp_ttype type = l.next(tl);
    if(type == CPP_NAME)
    {
	for(int i = 0;i < SerializeMethod::EN_MaxRule;++i)
	{
	    if(0 == Compare(tl,SerializeMethod::MethodTypeSpelling[i]))
	    {
		if(CPP_EOF != l.next(tl))
		{
		    warn(l) << "nothing should be apeared after "<<SerializeMethod::MethodTypeSpelling[i] <<std::endl;
		}
		AddMeta(new SerializeMethod(l.location(),(SerializeMethod::enMethodRule)i));
		return;
	    }
	}
	error(l) << "after selector 'method' should be one of the four method type :onserializing,onserialized,ondeserializing and ondeserialized"<<std::endl;
    }
}

void MetaParser::AddMeta(SerializeMeta* info)
{
    tree scope = current_scope();
    if(info->Is<Serializable>())
    {
	scope = global_namespace;
    }
    location_t loc = DECL_SOURCE_LOCATION(scope);
    //std::cout<<"add "<<scope<<":"<<loc<<":"<<LOCATION_LINE(loc)<<","<<LOCATION_COLUMN(loc)<<std::endl;
    mMetas[scope].insert(info);
}


