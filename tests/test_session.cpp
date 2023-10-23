#include <catch2/catch_test_macros.hpp>
#include "fff.h"
#include <atomic>
// #include <iostream>
DEFINE_FFF_GLOBALS;
extern "C"{

#include "session.h"
#include "plugin.h"
#include "log.h"
#include "utils.h"
#include "id_pool.h"
#include "resources.h"
FAKE_VALUE_FUNC(struct vaccel_plugin*, get_virtio_plugin);
FAKE_VALUE_FUNC(struct vaccel_session*, sess_free);
}

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_VACCEL_SESSIONS 1024

int mock_sess_init(vaccel_session* sess, uint32_t flags) {
    (void)sess;
    (void)flags;
    return 0;
}

int mock_sess_update(vaccel_session* sess, uint32_t flags) {
    (void)sess;
    (void)flags;
    return 0;
}

int mock_sess_free(vaccel_session* sess) {
    (void)sess;
    return 0;
}

int mock_sess_register(uint32_t sess_id, vaccel_id_t resource_id){
    (void) sess_id;
    (void) resource_id;
    return 0;
}

int mock_sess_unregister(uint32_t sess_id, vaccel_id_t resource_id){
    (void) sess_id;
    (void) resource_id;
    return 0;
}

// TEST_CASE("vaccel_sess_update", "[session]")
// {
//     sessions_bootstrap();
//     struct vaccel_session sess;
//     struct vaccel_resource res;


//     res.type = VACCEL_RES_CAFFE_MODEL;

//     int result = vaccel_sess_init(&sess,1);
//     REQUIRE(result == VACCEL_OK);

//     SECTION("change flag")
//     {   
//         result = vaccel_sess_update(&sess, 2);
//         REQUIRE(result == VACCEL_OK);
//     }

//     result = vaccel_sess_update(NULL,2);

//     REQUIRE(vaccel_sess_free(&sess) == VACCEL_OK);

//     sessions_cleanup();
// }

// TEST_CASE("session_sess_register", "[session]")
// {
//     struct vaccel_session sess;
//     sess.hint = 0;
//     struct vaccel_resource res;
//     res.type = VACCEL_RES_SHARED_OBJ;

//     int ret = sessions_bootstrap();
//     REQUIRE(VACCEL_OK == ret);

//     ret = vaccel_sess_init(&sess,1);
//     REQUIRE(VACCEL_OK == ret);


//     SECTION("null arguments")
//     {

//         REQUIRE(vaccel_sess_register(NULL, NULL) == VACCEL_EINVAL);
//         REQUIRE(vaccel_sess_register(NULL, &res) == VACCEL_EINVAL);
//         REQUIRE(vaccel_sess_register(&sess, NULL) == VACCEL_EINVAL);

//     }

//     SECTION("valid arguments")
//     {   
//         REQUIRE(vaccel_sess_register(&sess, &res) == VACCEL_OK);
//         REQUIRE(sess.resources != NULL);
//     }

// }

// int mock_sess_init(vaccel_session* session, uint32_t flags) {
//     return 0;
// }

TEST_CASE("session_sess", "[session]")
{

    struct vaccel_session test_sess;
    test_sess.hint = 0;
    struct vaccel_resource test_res;
    test_res.type = VACCEL_RES_SHARED_OBJ;

    

    int ret = sessions_bootstrap();
    REQUIRE(VACCEL_OK == ret);

    ret = resources_bootstrap();
    REQUIRE(VACCEL_OK == ret);

    ret = vaccel_sess_init(&test_sess,1);
    REQUIRE(VACCEL_OK == ret);

    SECTION("invalid null sess init")
    {
        ret = vaccel_sess_init(NULL,1);
        REQUIRE(VACCEL_EINVAL == ret);
    }

    ret = vaccel_sess_update(&test_sess, 2);
    REQUIRE(VACCEL_OK == ret);

    SECTION("invalid null sess update")
    {
        ret = vaccel_sess_update(NULL,0);
        REQUIRE(VACCEL_EINVAL == ret);
    }

    ret = vaccel_sess_register(&test_sess, &test_res);
    REQUIRE(VACCEL_OK == ret);

    SECTION("invalid null sess register")
    {
        ret = vaccel_sess_register(NULL,0);
        REQUIRE(VACCEL_EINVAL == ret);
    }


    ret = vaccel_sess_unregister(&test_sess, &test_res);
    REQUIRE(VACCEL_OK == ret);


    SECTION("invalid null sess unregister")
    {
        ret = vaccel_sess_unregister(NULL,0);
        REQUIRE(VACCEL_EINVAL == ret);
    }

    ret = vaccel_sess_free(&test_sess);
    REQUIRE(VACCEL_OK == ret);

    SECTION("invalid null ness free")
    {
        ret = vaccel_sess_free(NULL);
        REQUIRE(VACCEL_EINVAL == ret);
    }

    // ret = resources_cleanup();
    // REQUIRE(VACCEL_OK == ret);

    // ret = sessions_cleanup();
    // REQUIRE(VACCEL_OK == ret);
}


TEST_CASE("session_sess_virtio", "[session]")
{
    struct vaccel_session test_sess;
    test_sess.hint = 0;
    test_sess.session_id = 1;
    struct vaccel_resource test_res;
    test_res.type = VACCEL_RES_SHARED_OBJ;

    RESET_FAKE(get_virtio_plugin);

    // Create a mock plugin
    struct vaccel_plugin_info v_mock_info;
    v_mock_info.name = "fake_virtio";
    v_mock_info.sess_init = mock_sess_init;
    v_mock_info.sess_free = mock_sess_free;
    v_mock_info.sess_update = mock_sess_update;
    v_mock_info.sess_register = mock_sess_register;
    v_mock_info.sess_unregister = mock_sess_unregister;

    struct vaccel_plugin v_mock;
    v_mock.info = &v_mock_info;

    get_virtio_plugin_fake.return_val = &v_mock;

    int ret = sessions_bootstrap();
    REQUIRE(VACCEL_OK == ret);

    ret = resources_bootstrap();
    REQUIRE(VACCEL_OK == ret);

    ret = vaccel_sess_init(&test_sess, 1);
    REQUIRE(VACCEL_OK == ret);

    ret = vaccel_sess_update(&test_sess, 2);
    REQUIRE(VACCEL_OK == ret);

    ret = vaccel_sess_register(&test_sess, &test_res);
    REQUIRE(VACCEL_OK == ret);

    ret = vaccel_sess_unregister(&test_sess, &test_res);
    REQUIRE(VACCEL_OK == ret);

    ret = vaccel_sess_free(&test_sess);
    REQUIRE(VACCEL_OK == ret);

    REQUIRE(get_virtio_plugin_fake.call_count == 5);
}
