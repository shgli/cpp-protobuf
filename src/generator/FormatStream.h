#ifndef _SE_FORMATSTREAM_H
#define _SE_FORMATSTREAM_H
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "indent.h"
class FormatStream
{
    public:
	FormatStream(std::ostream& os,uint8 in = 4);

	FormatStream& Indent( void ){ mIndent.inc(); return *this;}
	FormatStream& Outdent( void ){ mIndent.dec(); return *this;}

	template<typename T>
	std::ostream& operator<< (const T v)
	{
		mOstream<<mIndent<<v;
		return mOstream;
	}

	std::ostream& operator<< (const std::string& v)
	{
	    mOstream<<mIndent<<v;
	    return mOstream;
	}

	std::ostream& BaseStream() { return mOstream;}
    private:
	std::ostream& mOstream;
	indent mIndent;

    public:
	struct BlockGuard
	{
	    typedef FormatStream type;
	    BlockGuard(FormatStream& fos);
	    BlockGuard(FormatStream& fos,const std::string& expr);

	
	    ~BlockGuard();
	private:
	    FormatStream& mStream;
	};

	struct CaseGuard
	{
	    typedef FormatStream type;
	    CaseGuard(FormatStream& fos,const std::string& expr);
	    ~CaseGuard();
	private:
	    FormatStream& mStream;
	};

};

#define BLOCKGUARD GuardAble<FormatStream::BlockGuard>
#define CASEGUARD GuardAble<FormatStream::CaseGuard>
#define BLOCK(fos) for(BLOCKGUARD  __guard__(fos);__guard__;)
#define BLOCK_EX(fos,expr) for(BLOCKGUARD __guard__(fos,expr);__guard__;)
#define CASE(fos,n) for(CASEGUARD __guard__(fos,boost::lexical_cast<std::string>(n));__guard__;)
#define FOR(fos,expr) BLOCK_EX(fos,std::string("for(") + expr + ")")
#define WHILE(fos,expr) BLOCK_EX(fos,std::string("while(") + expr + ")")
#define IF(fos,expr) BLOCK_EX(fos,std::string("if(") + expr + ")")
#define ELSE(fos) BLOCK_EX(fos,std::string("else"))
#define SWITCH(fos,expr) BLOCK_EX(fos,std::string("switch(") + expr + ")")
#define DEFAULT(fos) BLOCK_EX(fos,std::string("default:"))
#define NAMESPACE(fos,expr) BLOCK_EX(fos,std::string("namespace ") + expr)

 
#endif
