#include <catch2/catch_test_macros.hpp>
#include <fff.h>
#include <atomic>
DEFINE_FFF_GLOBALS;

extern "C"{
#include "session.h"
#include "plugin.h"
#include "log.h"
#include "utils.h"
#include "id_pool.h"
FAKE_VALUE_FUNC(int, id_pool_new, id_pool_t *, int);
}
#define MAX_VACCEL_SESSIONS 1024

struct vaccel_session test_sess;

extern struct {
	/* true if the sessions subsystem has been initialized */
	bool initialized;

	/* Available session ids */
	id_pool_t ids;

	/* Active sessions */
	struct vaccel_session *running_sessions[MAX_VACCEL_SESSIONS];
} sessions;

TEST_CASE( "vaccel_bootstrap", "[session]" ) {

    SECTION("cannot create a new id pool")
    {
        id_pool_new_fake.return_val = 1;
        REQUIRE(sessions_bootstrap() == 1);
        REQUIRE(sessions_cleanup() == VACCEL_OK);
    }
    
    SECTION("id pool created")
    {
        id_pool_new_fake.return_val = VACCEL_OK;
        REQUIRE(sessions_bootstrap() == VACCEL_OK);
        REQUIRE(sessions_cleanup() == VACCEL_OK);
    }
}
///