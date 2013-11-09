#include <cassert>
#include "ClassInfo.h"
#include "Utils.h"
#include "FieldInfo.h"
ClassInfo::ClassInfo(tree type)
    :mIsSerializable(false)
    ,mSyntaxTree(type)
    ,mIsCurrentUnit(false)
    ,mIsCollected(false)
{
    assert(nullptr != mSyntaxTree);
    std::memset(mMethodInfos,0,sizeof(mMethodInfos));
    if(nullptr != mSyntaxTree)
    {
	tree decl = TYPE_NAME(mSyntaxTree);
	mFileName = DECL_SOURCE_FILE(decl);
	if(mFileName == main_input_filename)
	{
	    mIsCurrentUnit = true;
	}

	mName = GetNameByTree(decl);
        mQName = GetDeclNamespace(decl) + "::" + mName;
    }
}

