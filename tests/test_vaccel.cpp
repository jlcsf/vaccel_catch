#include <catch2/catch_test_macros.hpp>
#include <fff.h>
#include <atomic>
DEFINE_FFF_GLOBALS;

extern "C"{
#include "plugin.h"
#include "session.h"
#include "log.h"

#define UNIT_TESTING
#include "vaccel.h"
#undef UNIT_TESTING

#include "resources.h"
#include "utils.h"

#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
}
// #define MAX_RUNDIR_PATH 1024
// static char rundir[MAX_RUNDIR_PATH];


// extern int create_vaccel_rundir_for_testing();
// TEST_CASE("Test create_vaccel_rundir", "[create_vaccel_rundir]") 
// {
//     int ret = create_vaccel_rundir_for_testing();
//     REQUIRE(ret == VACCEL_OK);
// }

TEST_CASE("valid")
{
    REQUIRE(1==1);
}

