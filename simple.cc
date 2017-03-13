#include <stdio.h>
#include <iostream>

#include "gcc-plugin.h"
#include "plugin.h"
#include "plugin-version.h"

#include "tree.h"
#include "tree-ssa-alias.h"
#include "basic-block.h"
#include "gimple-expr.h"
#include "gimple.h"
#include "gimple-pretty-print.h"
#include "tree-cfg.h"
#include "tree-pass.h"
#include "cfgloop.h"
#include "cgraph.h"
#include "options.h"
#include "dominance.h"
#include "pass_manager.h"
#include "context.h"
#include "rtl.h"
#include "tree-pass.h"
#include "tree-pretty-print.h"
#include "cfghooks.h"
#include "graph.h"

int plugin_is_GPL_compatible = 1;

struct plugin_info simple_plugin_info
{
  .version = "0.0.1",
  .help = "A simple plugin ..."
};

class SimpleGimplePass : public gimple_opt_pass
{
public:
  SimpleGimplePass(const pass_data& data, gcc::context *ctxt) :
    gimple_opt_pass(data, ctxt)
  {
  }

  bool gate (function *fun)
  {
    return true;
  }
  
  unsigned int execute (function *fun)
  {
    return 0;
  }

  opt_pass *clone()
  {
    return this;
  }
};

//#define DUMP_ALL

#if DUMP_ALL
#define print_context \
  printf("cfun = %p\n", cfun); \
  if (cfun) {\
    printf("cfun->decl = %p\n", cfun->decl);\
    if (cfun->decl) {                                      \
      print_generic_decl(stdout, cfun->decl, 0xFFFFFFFF);  \
      printf("\n"); \
    }\
    printf("cfun->gimple_body = %p\n", cfun->gimple_body);\
    if (cfun->gimple_body) {\
      print_gimple_seq(stdout, cfun->gimple_body, 4, 0xFFFFFFFF);\
      printf("\n");\
    };\
    printf("cfun->cfg = %p\n", cfun->cfg);      \
    if (cfun->cfg) \
    {\
      basic_block bb;\
      gimple_dump_cfg(stdout, 0xFFFFFFFF);       \
      FOR_ALL_BB_FN(bb, cfun)                    \
        dump_bb (stdout, bb, 4, 0xFFFFFFFF);     \
    } \
  }
#else
#define print_context \
  printf("cfun = %p\n", cfun); \
  if (cfun) {\
    printf("cfun->decl = %p\n", cfun->decl);\
    if (cfun->decl) {                                      \
      print_generic_decl(stdout, cfun->decl, 0);  \
      printf("\n"); \
    }\
    printf("cfun->cfg = %p\n", cfun->cfg);      \
    if (cfun->cfg) \
    {\
      basic_block bb;\
      printf("*** BASIC BLOCKS ***\n");      \
      FOR_ALL_BB_FN(bb, cfun)                    \
        {\
          printf("*** ========================");\
          dump_bb (stdout, bb, 4, 0xFFFFFFFF);  \
        }\
      print_graph_cfg("graph", cfun);        \
    } \
  }
#endif

// gcc_data is NULL;
void
on_plugin_finish(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin finished" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  print_context;
}

// gcc_data is opt_pass *
void
on_plugin_pass_execution(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin pass execution" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  opt_pass *pass = (opt_pass *)gcc_data;
  printf("pass name = %s\n", pass->name);
  printf("pass index = %d\n", pass->static_pass_number);
  
  if (!memcmp(pass->name , "*clean_state", 12))
    {
      printf("***>>> HERE <<<***\n");
      print_context;
    }
}

// gcc_data is opt_pass *
void
on_plugin_new_pass(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin new pass" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  opt_pass *pass = (opt_pass *)gcc_data;
  printf("pass name = %s\n", pass->name);
  printf("pass index = %d\n", pass->static_pass_number);
  
  print_context;
}

// gcc_data is NULL
void
on_plugin_finish_unit(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin finished unit" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  print_context;
}

// gcc_data is NULL
void
on_plugin_plugin_all_passes_start(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin PLUGIN_ALL_PASSES_START" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  print_context;
}

// gcc_data is NULL
void
on_plugin_plugin_all_passes_end(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin PLUGIN_ALL_PASSES_END" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  print_context;
}

// gcc_data is NULL
void
on_plugin_plugin_plugin_all_ipa_passes_start(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin PLUGIN_ALL_IPA_PASSES_START" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  print_context;
}

// gcc_data is NULL
void
on_plugin_plugin_plugin_all_ipa_passes_end(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cerr << "Simple plugin PLUGIN_ALL_IPA_PASSES_END" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  print_context;
}

// gcc_data is NULL
static void
trace_callback_for_PLUGIN_EARLY_GIMPLE_PASSES_END(void *gcc_data, void *user_data)
{
  std::cerr << "============================" << std::endl;
  std::cout << "PLUGIN_EARLY_GIMPLE_PASSES_END" << std::endl;
  std::cout << "    gcc_data = " << gcc_data << std::endl;
  std::cout << "   user_data = " << user_data << std::endl;

  print_context;
}

static int SimpleGimplePass_do_init(struct plugin_name_args *plugin_info,
                                    enum opt_pass_type pass_type,
                                    size_t pass_sz)
{
  pass_data pass_data;
  struct opt_pass *pass;

  std::cerr << "SimpleGimplePass_do_init: entry" << std::endl;
  
  memset(&pass_data, 0, sizeof(pass_data));

  pass_data.type = pass_type;
  pass_data.name = "gimple";

#if (GCC_VERSION < 5000)
  pass_data.has_gate = true;
  pass_data.has_execute = true;
#endif

  std::cerr << "SimpleGimplePass_do_init: pass_data.name = " << pass_data.name << std::endl;
  
  switch (pass_type)
    {
    case GIMPLE_PASS:
      std::cerr << "SimpleGimplePass_do_init: pass_type = GIMPLE_PASS " << std::endl;
      pass = new SimpleGimplePass(pass_data, g);
      break;
      
    default:
      gcc_unreachable();
    }

  struct register_pass_info rpinfo;

  rpinfo.pass = pass;
  rpinfo.pos_op = PASS_POS_REPLACE;  
  rpinfo.ref_pass_instance_number = 0;
  rpinfo.reference_pass_name = "gimple";
  
  std::cerr << "Registering callback ... " << pass_data.name << std::endl;
  
  register_callback (plugin_info->base_name, PLUGIN_EARLY_GIMPLE_PASSES_END,
                     trace_callback_for_PLUGIN_EARLY_GIMPLE_PASSES_END, NULL);

  return 0;
}

int plugin_init (struct plugin_name_args *plugin_info,
                 struct plugin_gcc_version *version)
{
  if (!plugin_default_version_check (version, &gcc_version))
    {
      std::cerr << "This GCC plugin is for version " << GCCPLUGIN_VERSION_MAJOR
                << "." << GCCPLUGIN_VERSION_MINOR << "\n";
      return 1;
    }

  std::cerr << "Plugin info\n";
  std::cerr << "===========\n\n";
  std::cerr << "Base name: " << plugin_info->base_name << "\n";
  std::cerr << "Full name: " << plugin_info->full_name << "\n";
  std::cerr << "Number of arguments of this plugin:" << plugin_info->
    argc << "\n";

  for (int i = 0; i < plugin_info->argc; i++)
    {
      std::cerr << "Argument " << i << ": Key: " << plugin_info->argv[i].
	key << ". Value: " << plugin_info->argv[i].value << "\n";
 
    }

  if (plugin_info->version != NULL)
    std::cerr << "Version string of the plugin: " << plugin_info->
      version << "\n";
  if (plugin_info->help != NULL)
    std::cerr << "Help string of the plugin: " << plugin_info->help << "\n";
  
  std::cerr << "\n";
  std::cerr << "Version info\n";
  std::cerr << "============\n\n";
  std::cerr << "Base version: " << version->basever << "\n";
  std::cerr << "Date stamp: " << version->datestamp << "\n";
  std::cerr << "Dev phase: " << version->devphase << "\n";
  std::cerr << "Revision: " << version->devphase << "\n";
  std::cerr << "Configuration arguments: " << version->
    configuration_arguments << "\n";
  std::cerr << "\n";
  
  /* Register at info for the plugin: */
  //  register_callback(plugin_info->base_name, PLUGIN_INFO,
  //                NULL, (void *)simple_plugin_info);

  
  /* Register at info for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_PASS_EXECUTION,
                    on_plugin_pass_execution, NULL);
  
  /* Register at info for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_NEW_PASS,
                    on_plugin_new_pass, NULL);
  
  /* Register at-exit finalization for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_FINISH,
                    on_plugin_finish, NULL);
  
  /* Register before first pass from all_passes  for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_PASSES_START,
                    on_plugin_plugin_all_passes_start, NULL);
  
  /* Register after last pass from all_passes for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_PASSES_END,
                    on_plugin_plugin_all_passes_end, NULL);
  
  /* Register before first ipa pass  for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_IPA_PASSES_START,
                    on_plugin_plugin_plugin_all_ipa_passes_start, NULL);
  
  /* Register after last ipa pass for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_IPA_PASSES_END,
                    on_plugin_plugin_plugin_all_ipa_passes_end, NULL);
  
  /* Register at-exit finalization for the plugin: */
  //  register_callback(plugin_info->base_name, PLUGIN_FINISH_PARSE_FUNCTION,
  //                    on_plugin_finish_parse_function, NULL);
  
  /* Register at-exit finalization for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_FINISH_UNIT,
                    on_plugin_finish_unit, NULL);
  
  SimpleGimplePass_do_init(plugin_info, GIMPLE_PASS, sizeof(struct gimple_opt_pass));

  std::cerr << "Plugin successfully initialized\n";
  
  return 0;  
}

  
