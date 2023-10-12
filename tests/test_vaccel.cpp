#include <catch2/catch_test_macros.hpp>
#include <fff.h>
#include <atomic>
DEFINE_FFF_GLOBALS;

extern "C"{
#include "vaccel.h"
}

TEST_CASE("vaccel_rundir valid", "[vaccel_rundir]") {
    // REQUIRE(vaccel_rundir() != nullptr);
    // int ret = VACCEL_EINVAL;
	// vaccel_log_init();

	// vaccel_debug("Initializing vAccel");
	// vaccel_info("vAccel %s", VACCELRT_VERSION);

	// ret = create_vaccel_rundir();
    // REQUIRE(ret == VACCEL_OK);
    // cleanup_vaccel_rundir();

    //use function pointers here
}

TEST_CASE("valid")
{
    REQUIRE(1==1);
}

