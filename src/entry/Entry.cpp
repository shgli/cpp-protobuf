#include <gcc.h> // Keep it first.

#include <memory>  // std::auto_ptr
#include <string>
#include <vector>
#include <cstring> // std::strcpy
#include <cassert>
#include <iostream>
#include "Plugin.h"
extern "C" void HandlePragma(struct cpp_reader*);

extern "C" void PragmasRegister(void*, void*)
{
  // GCC has a limited number of pragma slots and we have exhausted them.
  // A workaround is to make 'db' a pragma rather than a namespace. This
  // way we only have one pragma but the drawback of this approach is the
  // fact that the specifier or qualifier name will now be macro-expanded
  // (though this happens anyway if we have multiple specifiers in a single
  // pragma). Once the GCC folks fix this, we can go back to the namespace
  // approach.
  //
  c_register_pragma_with_expansion (0, "protobuf", HandlePragma);
}

extern "C" void HandlePragma(struct cpp_reader*)
{
    Plugin::Instance().ParseMeta();
}

extern "C" void HandleGateCallback(void*,void*)
{
    // If there were errors during compilation, let GCC handle the
    // exit.
    //
    if (errorcount || sorrycount)
	return;

    Plugin::Instance().CollectTypes();
    Plugin::Instance().Generate();
    exit(0);
}

extern "C" int plugin_init (plugin_name_args* plugin_info, plugin_gcc_version*)
{
    // Disable assembly output.
    //
    asm_file_name = HOST_BIT_BUCKET;


    // Register callbacks.
    register_callback (plugin_info->base_name,
	    PLUGIN_PRAGMAS,
	    PragmasRegister,
	    0);

    register_callback (plugin_info->base_name,
	    PLUGIN_OVERRIDE_GATE,
	    &HandleGateCallback,
	    0);
    return 0;
}

