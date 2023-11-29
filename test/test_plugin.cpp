#include <catch2/catch_test_macros.hpp>

extern "C" {
#include "plugin.h"
#include "error.h"
#include "list.h"
}

#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

static const char *pname = "mock_plugin_test";

void dummy_function() {}

static int fini(void)
{
    return VACCEL_OK;
} 
static int init(void)
{
    return VACCEL_OK;
}

static int no_op_exec(){return 2;}

TEST_CASE("plugin_test_basic_test", "[plugin_tests]")
{
    struct vaccel_plugin plugin_test;
    struct vaccel_plugin_info pinfo;

    pinfo.name = pname;
    pinfo.init = init;
    pinfo.fini = fini;

    list_init_entry(&plugin_test.entry);
    list_init(&plugin_test.ops); 
    
    plugin_test.info = &pinfo;

    int ret;
    ret = plugins_bootstrap();
    REQUIRE(ret == VACCEL_OK);

    ret = register_plugin(&plugin_test);
    REQUIRE(ret == VACCEL_OK);

    struct vaccel_op exec_operation;
    exec_operation.type = VACCEL_EXEC;
    exec_operation.func = (void *)no_op_exec;
    exec_operation.owner = &plugin_test;

    ret = register_plugin_function(&exec_operation);
    REQUIRE(ret == VACCEL_OK);

    ret = unregister_plugin(&plugin_test);
    REQUIRE(ret == VACCEL_OK);

    ret = plugins_shutdown();
    REQUIRE(ret == VACCEL_OK);

}