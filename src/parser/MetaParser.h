#ifndef _SE_METAPARSER_H
#define _SE_METAPARSER_H 
#include "Metas.h"
class cxx_pragma_lexer;
class MetaParser
{
public:
    void Parse( void );

    SerializeMetas& Metas( void ) { return mMetas;}
    const SerializeMetas& Metas( void ) const { return mMetas;}
private:
    void ParseSerializable(cxx_pragma_lexer& lexer);
    void ParseFieldMeta(cxx_pragma_lexer& lexer);
    void ParseMethodMeta(cxx_pragma_lexer& lexer);
    void AddMeta(SerializeMeta* info);
    DefaultValue ParseDefaultValue(cxx_pragma_lexer& l,cpp_ttype& type,std::string& tl,tree& tn);

    SerializeMetas mMetas;
};
#endif

