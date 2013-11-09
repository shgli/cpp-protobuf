#ifndef _SE_SERIALIZEMETA_H
#define _SE_SERIALIZEMETA_H 
#include <set>
#include <string>
#include <map>
#include <vector>
#include "gcc.h"
#include "Comparator.h"
#include "DefaultValue.h"

class SerializeMeta
{
private:
    location_t mLocation;

public:
    SerializeMeta(location_t loc)
	:mLocation(loc)
    {}

    virtual ~SerializeMeta(){}
    location_t Location() const {return mLocation;}

    template<typename T>
    bool Is( void )const { return nullptr != dynamic_cast<const T*>(this);}

};

struct MetaCompare
{
    bool operator() (const SerializeMeta* l,const SerializeMeta* r)
    { 
        return l->Location() < r->Location();
    }
};

typedef std::set<SerializeMeta*,MetaCompare> SerializeMetaSet;
typedef std::map<tree,SerializeMetaSet,tree_comparator> SerializeMetas;


#endif

