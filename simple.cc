#define simple_malloc(p)      malloc((p))
#define simple_calloc(n, x)   calloc((n), (x))
#define simple_realloc(p, x)  realloc((p), (x))
#define simple_free(x)        free((x))

#include <stdio.h>
#include <iostream>

#include "gcc-plugin.h"
#include "plugin.h"
#include "plugin-version.h"

#include <assert.h>

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

class simple_plugin_t
{
public:
  simple_plugin_t(struct plugin_name_args *);
  virtual ~simple_plugin_t(void);

  bool has_arg(const char *key);
  
  const char *get_graphname(void);

protected:
  simple_plugin_t(void);
  simple_plugin_t(simple_plugin_t &);
  simple_plugin_t& operator =(simple_plugin_t &);
  simple_plugin_t *clone(simple_plugin_t *);

private:
  std::string m_base_name;
  std::string m_full_name;
  int m_argc;
  struct plugin_argument *m_argv;
  std::string m_version;
  std::string m_help;
  std::string m_graphname;
};

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
      if (pi->has_arg("graphname")) \
        print_graph_cfg(pi->get_graphname(), cfun);     \
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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

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

  simple_plugin_t *pi = (simple_plugin_t *)user_data;

  print_context;
}

simple_plugin_t::simple_plugin_t(struct plugin_name_args *args)
{
  std::cout << "simple_plugin_t::simple_plugin_t(struct plugin_name_args *args): entry" << std::endl;

  m_graphname = "";
  m_base_name = args->base_name != NULL ? args->base_name : "";
  m_full_name = args->full_name != NULL ? args->full_name : "";
  m_argc = args->argc;

  m_argv = (struct plugin_argument *)simple_calloc(sizeof(struct plugin_argument), m_argc);
  assert(m_argv != (struct plugin_argument *)NULL);
  for (int i = 0 ; i < args->argc; i++)
    {
      m_argv[i].key = (char *)simple_malloc(strlen(args->argv[i].key));
      assert(m_argv[i].key != (char *)NULL);
      memcpy(m_argv[i].key, args->argv[i].key, strlen(args->argv[i].key)+1);

      m_argv[i].value = (char *)simple_malloc(strlen(args->argv[i].value));
      assert(m_argv[i].value != (char *)NULL);
      memcpy(m_argv[i].value, args->argv[i].value, strlen(args->argv[i].value)+1);

      if (!strncmp(args->argv[i].key, "graphname", 9))
        m_graphname = args->argv[i].value;
    }

  m_version = args->version ? args->version : "";
  m_help = args->help ? args->help : "";

  std::cout << "simple_plugin_t::simple_plugin_t(struct plugin_name_args *args): exit" << std::endl << std::endl;
}

simple_plugin_t::~simple_plugin_t()
{
  std::cout << "simple_plugin_t::~simple_plugin_t(): entry" << std::endl;

  //  if (m_argv)
  //free((void *)m_argv);

  std::cout << "simple_plugin_t::~simple_plugin_t(): exit" << std::endl;
}

bool
simple_plugin_t::has_arg(const char *key)
{
  bool ret = false;

  std::cout << "bool simple_plugin_t::has_arg(const char *key): entry" << std::endl;
  for (int i = 0 ; i < m_argc; i++)
    {
      if (!strncmp(m_argv[i].key, key, strlen(m_argv[i].key)))
        {
          ret = true;
          break;
        }
    }
  std::cout << "bool simple_plugin_t::has_arg(const char *key): exit [" << (ret ? "true" : "false") << "]" << std::endl;
  return ret;
}

const char *
simple_plugin_t::get_graphname(void)
{
  std::cout <<  "const char *simple_plugin_t::get_graphname(void): entry" << std::endl;
  std::cout <<  "const char *simple_plugin_t::get_graphname(void): m_graphname = " << m_graphname << std::endl;
  std::cout <<  "const char *simple_plugin_t::get_graphname(void): exit" << std::endl;
  return m_graphname.c_str();
}

simple_plugin_t::simple_plugin_t()
{
  std::cout << "simple_plugin_t::simple_plugin_t(): entry" << std::endl;
  std::cout << "simple_plugin_t::simple_plugin_t(): exit" << std::endl;
}

simple_plugin_t::simple_plugin_t(simple_plugin_t &plugin)
{
  std::cout << "simple_plugin_t::simple_plugin_t(simple_plugin_t &plugin): entry" << std::endl;
  std::cout << "simple_plugin_t::simple_plugin_t(simple_plugin_t &plugin): copy of plugin " << plugin.m_base_name << std::endl;

  m_base_name = plugin.m_base_name != (char *)NULL ? plugin.m_base_name : "";
  m_full_name = plugin.m_full_name != (char *)NULL ? plugin.m_full_name : "";
  m_argc = plugin.m_argc;
  m_argv = (struct plugin_argument *)simple_calloc(m_argc, sizeof(struct plugin_argument));
  assert(m_argv != (struct plugin_argument *)NULL);
  for (int i = 0 ; i < m_argc; i++)
    {
      m_argv[i].key = (char *)simple_malloc(strlen(plugin.m_argv[i].key));
      assert(m_argv[i].key != (char *)NULL);
      memcpy(m_argv[i].key, plugin.m_argv[i].key, strlen(plugin.m_argv[i].key)+1);

      m_argv[i].value = (char *)simple_malloc(strlen(plugin.m_argv[i].value));
      assert(m_argv[i].value != (char *)NULL);
      memcpy(m_argv[i].value, plugin.m_argv[i].value, strlen(plugin.m_argv[i].value)+1);

      if (!strncmp(plugin.m_argv[i].key, "graphname", 9))
        m_graphname = plugin.m_argv[i].value;
    }
  m_version = plugin.m_version != (char *)NULL ? plugin.m_version : "";
  m_help = plugin.m_help != (char *)NULL ? plugin.m_help : "";
  
  std::cout << "simple_plugin_t::simple_plugin_t(simple_plugin_t &plugin): exit" << std::endl;
}

simple_plugin_t& simple_plugin_t::operator =(simple_plugin_t &plugin)
{
  std::cout << "simple_plugin_t& simple_plugin_t::operator =(simple_plugin_t &plugin): entry" << std::endl;
  std::cout << "simple_plugin_t& simple_plugin_t::operator =(simple_plugin_t &plugin): assign of plugin " << plugin.m_base_name << std::endl;

  m_base_name = plugin.m_base_name != (char *)NULL ? plugin.m_base_name : "";
  m_full_name = plugin.m_full_name != (char *)NULL ? plugin.m_full_name : "";
  m_argc = plugin.m_argc;
  m_argv = (struct plugin_argument *)simple_calloc(plugin.m_argc, sizeof(struct plugin_argument));
  assert(m_argv != (struct plugin_argument *)NULL);
  for (int i = 0 ; i < m_argc; i++)
    {
      m_argv[i].key = (char *)simple_malloc(strlen(plugin.m_argv[i].key));
      assert(m_argv[i].key != (char *)NULL);
      memcpy(m_argv[i].key, plugin.m_argv[i].key, strlen(plugin.m_argv[i].key)+1);

      m_argv[i].value = (char *)simple_malloc(strlen(plugin.m_argv[i].value));
      assert(m_argv[i].value != (char *)NULL);
      memcpy(m_argv[i].value, plugin.m_argv[i].value, strlen(plugin.m_argv[i].value)+1);

      if (!strncmp(plugin.m_argv[i].key, "graphname", 9))
        m_graphname = plugin.m_argv[i].value;
    }
  m_version = plugin.m_version != (char *)NULL ? plugin.m_version : "";
  m_help = plugin.m_help != (char *)NULL ? plugin.m_help : "";
  
  std::cout << "simple_plugin_t& simple_plugin_t::operator =(simple_plugin_t &plugin): exit" << std::endl;
  return *this;
}

simple_plugin_t *simple_plugin_t::clone(simple_plugin_t *plugin_ptr)
{
  std::cout << "simple_plugin_t *simple_plugin_t::clone(simple_plugin_t *plugin_ptr): entry" << std::endl;
  std::cout << "simple_plugin_t *simple_plugin_t::clone(simple_plugin_t *plugin_ptr): assign of plugin " << plugin_ptr->m_base_name << std::endl;

  m_base_name = plugin_ptr->m_base_name != (char *)NULL ? plugin_ptr->m_base_name : "";
  m_full_name = plugin_ptr->m_full_name != (char *)NULL ? plugin_ptr->m_full_name : "";
  m_argc = plugin_ptr->m_argc;
  m_argv = (struct plugin_argument *)simple_calloc(m_argc, sizeof(struct plugin_argument));
  if (m_argv == (struct plugin_argument *)NULL)
    return (simple_plugin_t *)NULL;
  for (int i = 0 ; i < m_argc; i++)
    {
      m_argv[i].key = (char *)simple_malloc(strlen(plugin_ptr->m_argv[i].key));
      assert(m_argv[i].key != (char *)NULL);
      memcpy(m_argv[i].key, plugin_ptr->m_argv[i].key, strlen(plugin_ptr->m_argv[i].key)+1);

      m_argv[i].value = (char *)simple_malloc(strlen(plugin_ptr->m_argv[i].value));
      assert(m_argv[i].value != (char *)NULL);
      memcpy(m_argv[i].value, plugin_ptr->m_argv[i].value, strlen(plugin_ptr->m_argv[i].value)+1);

      if (!strncmp(plugin_ptr->m_argv[i].key, "graphname", 9))
        m_graphname = plugin_ptr->m_argv[i].value;
    }
  m_version = plugin_ptr->m_version != (char *)NULL ? plugin_ptr->m_version : "";
  m_help = plugin_ptr->m_help != (char *)NULL ? plugin_ptr->m_help : "";
  
  std::cout << "simple_plugin_t *simple_plugin_t::clone(simple_plugin_t *plugin_ptr): exit" << std::endl;
  return this;
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
  simple_plugin_t *plugin_instance = new simple_plugin_t(plugin_info);
  assert(plugin_instance != (simple_plugin_t *)NULL);
  
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

  if (plugin_info->version != (char *)NULL)
    std::cerr << "Version string of the plugin: " << plugin_info->
      version << "\n";
  if (plugin_info->help != (char *)NULL)
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
                    on_plugin_pass_execution, (void *)plugin_instance);
  
  /* Register at info for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_NEW_PASS,
                    on_plugin_new_pass, (void *)plugin_instance);
  
  /* Register at-exit finalization for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_FINISH,
                    on_plugin_finish, (void *)plugin_instance);
  
  /* Register before first pass from all_passes  for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_PASSES_START,
                    on_plugin_plugin_all_passes_start, (void *)plugin_instance);
  
  /* Register after last pass from all_passes for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_PASSES_END,
                    on_plugin_plugin_all_passes_end, (void *)plugin_instance);
  
  /* Register before first ipa pass  for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_IPA_PASSES_START,
                    on_plugin_plugin_plugin_all_ipa_passes_start, (void *)plugin_instance);
  
  /* Register after last ipa pass for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_ALL_IPA_PASSES_END,
                    on_plugin_plugin_plugin_all_ipa_passes_end, (void *)plugin_instance);
  
  /* Register at-exit finalization for the plugin: */
  //  register_callback(plugin_info->base_name, PLUGIN_FINISH_PARSE_FUNCTION,
  //                    on_plugin_finish_parse_function, (void *)plugin_instance);
  
  /* Register at-exit finalization for the plugin: */
  register_callback(plugin_info->base_name, PLUGIN_FINISH_UNIT,
                    on_plugin_finish_unit, (void *)plugin_instance);
  
  SimpleGimplePass_do_init(plugin_info, GIMPLE_PASS, sizeof(struct gimple_opt_pass));

  std::cerr << "Plugin successfully initialized\n";
  
  return 0;  
}

  
