#include <catch2/catch_test_macros.hpp>
#include <fff.h>
#include <atomic>
// #include <iostream>
DEFINE_FFF_GLOBALS;
extern "C"{
#include "session.h"
// #include "plugin.h"
// #include "log.h"
// #include "utils.h"
// #include "id_pool.h"
// #include "resources.h"
// FAKE_VALUE_FUNC(int, id_pool_new, id_pool_t *, int);
}

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_VACCEL_SESSIONS 1024


// TEST_CASE("vaccel_bootstrap", "[session]") 
// {

//     SECTION("cannot create a new id pool")
//     {
//         id_pool_new_fake.return_val = 1;
//         REQUIRE(sessions_bootstrap() == 1);
//         REQUIRE(sessions_cleanup() == VACCEL_OK);
//     }
    
//     SECTION("id pool created")
//     {
//         id_pool_new_fake.return_val = VACCEL_OK;
//         REQUIRE(sessions_bootstrap() == VACCEL_OK);
//         REQUIRE(sessions_cleanup() == VACCEL_OK);
//     }
// }

TEST_CASE("vaccel_cleanup", "[session]")
{
    sessions_bootstrap();
    REQUIRE(sessions_cleanup() == VACCEL_OK);
}

TEST_CASE("vaccel_sess_register", "[session]")
{
    sessions_bootstrap();
    struct vaccel_session sess;
    struct vaccel_resource res;

    res.type = VACCEL_RES_MAX;



    SECTION("null arguments")
    {

        REQUIRE(vaccel_sess_register(NULL, NULL) == VACCEL_EINVAL);
        REQUIRE(vaccel_sess_register(NULL, &res) == VACCEL_EINVAL);
        REQUIRE(vaccel_sess_register(&sess, NULL) == VACCEL_EINVAL);

    }

    SECTION("valid arguments")
    {
        //REQUIRE(vaccel_sess_register(&sess, &res) == VACCEL_OK);
        //REQUIRE(sess.resources != NULL);
    }

}

TEST_CASE("vaccel_sess_init_null", "[session]")
{
    REQUIRE(vaccel_sess_init(NULL,0) == VACCEL_EINVAL);
}

TEST_CASE("vaccel_sess_init", "[session]")
{   

    struct vaccel_session sess;
    int ret = vaccel_sess_init(&sess, 0);
    REQUIRE(ret == VACCEL_OK);
}

// TEST_CASE("vaccel_sess_init_not_initialized", "[session]")
// {
//     struct vaccel_session sess;

//     struct {
//         bool initialized;
//         id_pool_t ids;
//         struct vaccel_session *running_sessions[MAX_VACCEL_SESSIONS];
//     } sessions;
    
//     sessions.initialized = false;
//     REQUIRE(vaccel_sess_init(&sess,0) == VACCEL_ESESS);

//     (void)sessions;
// }