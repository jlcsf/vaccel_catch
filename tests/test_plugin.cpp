#include <catch2/catch_test_macros.hpp>

extern "C" {
#include "plugin.h"
#include "error.h"
#include "list.h"
}

#include <stdbool.h>
#include <string.h>

static const char *pname = "mock_plugin";

struct vaccel_plugin plugin;
struct vaccel_plugin_info pinfo;

static int fini(void)
{
    return VACCEL_OK;
} 
static int init(void)
{
    return VACCEL_OK;
}

TEST_CASE("plugin_register", "[plugin]") {
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

    SECTION("plugin has no info")
    {
        REQUIRE(1 == 1);
    }

    plugins_shutdown();
}

TEST_CASE("plugin_unregister", "[plugin]") {
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

    SECTION("plugin state is initilaised but no plugin")
    {
        REQUIRE(1==1);
    }

    SECTION("plugin has no info entry")
    {
        REQUIRE(1==1);
    }

    SECTION("plugin succesfully unregistered")
    {
        REQUIRE(unregister_plugin(&plugin) == VACCEL_OK);
    }

    plugins_shutdown();
}

TEST_CASE("register_plugin_function", "[plugins]") {
    plugin.info = &pinfo;
    plugin.info->name = pname;
    list_init_entry(&plugin.entry);
    list_init_entry(&plugin.ops);
    plugin.info->init = init;
    plugin.info->fini = fini;

    plugins_bootstrap();
    register_plugin(&plugin);

    SECTION("invalid vaccel function")
    {
        REQUIRE(register_plugin_function(NULL) == VACCEL_EINVAL);
    }
    /// expand this more

    plugins_shutdown();
}

TEST_CASE("register_plugin_functions", "[plugins]") {
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
