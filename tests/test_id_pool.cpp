#include <catch2/catch_test_macros.hpp>
#include <fff.h>
#include <atomic>
DEFINE_FFF_GLOBALS;

extern "C"{
#include "id_pool.h"
#include "error.h"
}

TEST_CASE("id_pool_new", "[id_pool]")
{
    id_pool_t test_pool;
    REQUIRE(id_pool_new(&test_pool, 10) == VACCEL_OK);
}

TEST_CASE("id_pool_destroy", "[id_pool]")
{
    id_pool_t test_pool;
    REQUIRE(id_pool_new(&test_pool, 10) == VACCEL_OK);
    REQUIRE(id_pool_destroy(&test_pool) == VACCEL_OK);
}

TEST_CASE("id_pool_get", "[id_pool]")
{
    id_pool_t test_pool;
    id_pool_new(&test_pool, 3);
    vaccel_id_t id_test = id_pool_get(&test_pool);
    REQUIRE(id_test == 1);
    id_test = id_pool_get(&test_pool);
    REQUIRE(id_test == 2);
    id_test = id_pool_get(&test_pool);
    REQUIRE(id_test == 3);

    /// No more ids

    id_test = id_pool_get(&test_pool);
    REQUIRE(id_test == 0);
}