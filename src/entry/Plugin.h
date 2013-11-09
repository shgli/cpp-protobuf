#ifndef _SE_PLUGIN_H
#define _SE_PLUGIN_H
#include <memory>
#include "Singleton.h"
#include "Generator.h"
#include "Collector.h"
#include "MetaParser.h"
class MetaParser;
class Plugin:public Singleton<Plugin>
{
public:
    void ParseMeta();
    void CollectTypes();
    void Generate();
private:
    Plugin();

    void BuildGenerateInfos(ClassesT& classes,DependenciesT& dependencies,const ClassInfoMap& classInfos,const DependencySet dset);
    SerializeCallback GetCallbackType(SerializeMethod::enMethodRule rule);

    friend class Singleton<Plugin>;
    std::unique_ptr<MetaParser> mMetaParser;
    std::unique_ptr<Collector> mCollector;
    std::unique_ptr<Generator> mGenerator;
};
#endif
 
