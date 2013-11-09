#ifndef _CPP_PROTOBUF_INDENT_H
#define _CPP_PROTOBUF_INDENT_H
#include <string>
typedef unsigned char uint8;

class indent
{
    uint8 spaces_;
    uint8 indents_;
public:
    indent(uint8 space = 4)
	:spaces_(space)
	,indents_(0)
    {}

    inline indent& inc(uint8 in = 1)
    {
	indents_ += in;
	return *this;
    }

    inline indent& dec(uint8 in = 1)
    {
	if(indents_ >= in)
	{
	    indents_ -= in;
	}
	else
	{
	    indents_ = 0;
	}
	return *this;
    }

    friend std::ostream& operator<<(std::ostream& os,const indent& in);
};
#endif

