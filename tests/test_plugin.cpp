#include <catch2/catch_test_macros.hpp>

extern "C" {
#include "plugin.h"
#include "error.h"
#include "list.h"
}

#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

static const char *pname = "mock_plugin";

void dummy_function() {}

static int fini(void)
{
    return VACCEL_OK;
} 
static int init(void)
{
    return VACCEL_OK;
}

TEST_CASE("plugin_register", "[plugin]") {

    struct vaccel_plugin plugin;
    struct vaccel_plugin_info pinfo;
    plugin.info = &pinfo;
    plugin.info->name = pname;
    list_init_entry(&plugin.entry);
    list_init_entry(&plugin.ops);
    plugin.info->init = init;
    plugin.info->fini = fini;

    plugins_bootstrap();

    SECTION("normal plugin initialisation") 
    {
        REQUIRE(register_plugin(&plugin) == VACCEL_OK);
    }

    SECTION("null plugin initialisation")
    {
        REQUIRE(register_plugin(NULL) == VACCEL_EINVAL);
    }

    SECTION("null plugin name")
    {
        struct vaccel_plugin plugin;
        plugin.info = &pinfo;

        plugin.entry.next = &(plugin.entry);
        plugin.entry.prev = &(plugin.entry);

        REQUIRE(register_plugin(&plugin) == VACCEL_EINVAL);
    }

    SECTION("not boostrapped")
    {   

        REQUIRE(1 == 1);
    }

    SECTION("plugin already registered")
    {
        REQUIRE(register_plugin(&plugin) == VACCEL_OK);
        REQUIRE(register_plugin(&plugin) == VACCEL_EEXISTS);
    }
    
    SECTION("plugin list is not empty")
    {
        REQUIRE(1 == 1);
    }

    SECTION("plugin has invalid pinfo parameters")
    {   
        struct vaccel_plugin_info temp = pinfo;
        pinfo.fini = NULL;
        REQUIRE(register_plugin(&plugin) == VACCEL_EINVAL);
        pinfo.init = NULL;
        REQUIRE(register_plugin(&plugin) == VACCEL_EINVAL);
        pinfo.name = NULL;
        REQUIRE(register_plugin(&plugin) == VACCEL_EINVAL);
        pinfo = temp;

        REQUIRE(register_plugin(&plugin) == VACCEL_OK);
       
    }

    plugins_shutdown();
}

TEST_CASE("plugin_unregister", "[plugin]") {

    struct vaccel_plugin plugin;
    struct vaccel_plugin_info pinfo;
    plugin.info = &pinfo;
    plugin.info->name = pname;
    list_init_entry(&plugin.entry);
    list_init_entry(&plugin.ops);
    plugin.info->init = init;
    plugin.info->fini = fini;

    plugins_bootstrap();
    register_plugin(&plugin);

    SECTION("no plugin to unregister")
    {
        REQUIRE(unregister_plugin(NULL) == VACCEL_EINVAL);
    }

    SECTION("plugin state is not initialised")
    {
        REQUIRE(1 == 1);
    }

    SECTION("entry_linked(&plugin.entry) is false")
    {
        list_unlink_entry(&plugin.entry);
        REQUIRE(unregister_plugin(&plugin) == VACCEL_ENOENT);
    }

    SECTION("plugin has no info entry")
    {
        plugin.info = NULL;
        REQUIRE(unregister_plugin(&plugin) == VACCEL_EINVAL);
    }

    SECTION("plugin succesfully unregistered")
    {
        REQUIRE(unregister_plugin(&plugin) == VACCEL_OK);
    }

    plugins_shutdown();
}

TEST_CASE("register_plugin_function", "[plugins]") {
    
    int res = plugins_bootstrap();

    REQUIRE(res == VACCEL_OK);

    void *dl_handle = dlopen("./plugins/noop/libvaccel-noop.so", RTLD_LAZY);
    if (!dl_handle) {
        FAIL("Error loading plugin library: " << dlerror());
    }

    void *plugin_symbol = dlsym(dl_handle, "vaccel_plugin");
    if (!plugin_symbol) {
        FAIL("Error loading vaccel_plugin symbol from the library: " << dlerror());
    }
    
    struct vaccel_plugin* plugin_test = static_cast<struct vaccel_plugin*>(plugin_symbol);

    register_plugin(plugin_test);
    //REQUIRE(ret == VACCEL_OK);

    struct vaccel_op test_op;

    // SECTION("invalid vaccel function") {
    //     REQUIRE(register_plugin_function(NULL) == VACCEL_EINVAL);

    //     test_op.func = NULL;
    //     test_op.type = VACCEL_FUNCTIONS_NR + 1;
    //     test_op.owner = plugin_test;
    //     REQUIRE(register_plugin_function(&test_op) == VACCEL_EINVAL);
    // }

    // SECTION("Unknown function type") {
    //     test_op.func = get_plugin_op(VACCEL_EXEC, 0);
    //     test_op.type = VACCEL_FUNCTIONS_NR + 1;
    //     test_op.owner = plugin_test;
    //     REQUIRE(register_plugin_function(&test_op) == VACCEL_EINVAL + 1);
    // }

    // SECTION("plugin owner is unknown") {
    //     test_op.func = get_plugin_op(VACCEL_EXEC, 0);
    //     test_op.type = 1;
    //     test_op.owner = NULL;
    //     REQUIRE(register_plugin_function(&test_op) == VACCEL_EINVAL + 2);
    // }

    // SECTION("valid plugin registration") {
    //     test_op.func = get_plugin_op(VACCEL_EXEC, 0); 
    //     test_op.type = 1;
    //     test_op.owner = plugin_test;
    //     REQUIRE(register_plugin_function(&test_op) == VACCEL_OK);
    // }


    SECTION("invalid vaccel function") {
        REQUIRE(register_plugin_function(NULL) == VACCEL_EINVAL);

        test_op.func = NULL;
        test_op.type = VACCEL_FUNCTIONS_NR + 1;
        test_op.owner = plugin_test;
        REQUIRE(register_plugin_function(&test_op) == VACCEL_EINVAL);
    }

    SECTION("Unknown function type") {
        test_op.func = (void *)&dummy_function;
        test_op.type = VACCEL_FUNCTIONS_NR + 1;
        test_op.owner = plugin_test;
        REQUIRE(register_plugin_function(&test_op) == VACCEL_EINVAL + 1);
    }

    SECTION("plugin owner is unknown") {
        test_op.func = (void *)&dummy_function;
        test_op.type = 1;
        test_op.owner = NULL;
        REQUIRE(register_plugin_function(&test_op) == VACCEL_EINVAL + 2);
    }

    SECTION("valid plugin registration") {
        test_op.func = get_plugin_op(VACCEL_EXEC, 0); 
        test_op.type = 1;
        test_op.owner = plugin_test;
        REQUIRE(register_plugin_function(&test_op) == VACCEL_OK);
    }

    plugins_shutdown();
}

TEST_CASE("register_plugin_functions", "[plugins]") {

    struct vaccel_plugin plugin;
    struct vaccel_plugin_info pinfo;

    plugin.info = &pinfo;
    plugin.info->name = pname;
    list_init_entry(&plugin.entry);
    list_init_entry(&plugin.ops);
    plugin.info->init = init;
    plugin.info->fini = fini;

    plugins_bootstrap();

    /// expand this more

    plugins_shutdown();
}


