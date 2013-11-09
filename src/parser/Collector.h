#ifndef _SE_COLLECTOR_H
#define _SE_COLLECTOR_H
#include <string>
#include <map>
#include "Metas.h"

class cxx_lexer;
class ClassInfo;
typedef std::map<tree,ClassInfo*,tree_comparator> ClassInfoMap;
typedef std::set<std::string> DependencySet;
class Collector
{
public:
    void Collect(SerializeMetas& metas);

    const ClassInfoMap& ClassInfos()const { return mClassInfoMap;}
    const DependencySet& Dependencies()const { return mDependencies;}

#ifdef _DEBUG
    void PrintClassInfos() const;
#endif
private:
    void Collect(tree ns);
    void CollectType(tree t);
    void CollectMethodInfo(ClassInfo* pClassInfo,const SerializeMetaSet& infos);
    void CollectFieldInfo(ClassInfo* pClassInfo,const SerializeMetaSet& infos);
    void CollectBaseInfo(ClassInfo* pClassInfo);
    bool AddDecl(tree decl);

    ClassInfoMap mClassInfoMap;
    ClassInfoMap mDeclInfoMap;
    DependencySet mDependencies;

    static const int LOOSE_LIMIT = 3;
    friend std::ostream& operator<<(std::ostream& os,const Collector& p);
};
#endif
 
