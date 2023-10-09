#include <catch2/catch_test_macros.hpp>

#include "error.h"
#include "fpga.h"
#include "session.h"


TEST_CASE("vaccel_fpga_add", "[vaccel_fpga_plugins]")
{
    struct vaccel_session sess;
    float A[] = {1, 2, 3, 4, 5};
    float B[] = {1, 2, 6, 4, 5};
    float C[] = {1, 2, 6, 4, 5};

    size_t len_A = sizeof(A) / sizeof(A[0]);
    size_t len_B = sizeof(B) / sizeof(B[0]);
    
    SECTION("null session")
    {
        REQUIRE(vaccel_fpga_vadd(NULL, A, B, C, len_A, len_B) ==  VACCEL_EINVAL);
    }

    SECTION("valid session and inputs")
    {
        int ret = vaccel_sess_init(&sess, 0);
        REQUIRE(ret == VACCEL_OK);
        ret = vaccel_fpga_vadd(&sess, A, B, C, len_A, len_B);
        float C_expected[] = {2,4,9,8,10};
        size_t len_C = sizeof(C) / sizeof(C[0]);
        size_t len_C_expected = sizeof(C_expected) / sizeof(C_expected[0]);

        REQUIRE(vaccel_sess_free(&sess) == VACCEL_OK);
        REQUIRE(ret != VACCEL_ENOTSUP);

        REQUIRE(len_C == len_C_expected);
        
        REQUIRE(std::equal(C, C + len_C, C_expected));
    }

}

TEST_CASE("vaccel_fpga_copy", "[vaccel_fpga_plugins]")
{
    struct vaccel_session sess;
    int A[] = {1, 2, 3, 4, 5};
    int B[] = {1, 1, 1, 1, 1};

    size_t len_A = sizeof(A) / sizeof(A[0]);
    size_t len_B = sizeof(B) / sizeof(B[0]);
    
    SECTION("null session")
    {
        REQUIRE(vaccel_fpga_arraycopy(NULL, A, B, len_A) ==  VACCEL_EINVAL);
    }

    SECTION("valid session and inputs")
    {
        int ret = vaccel_sess_init(&sess, 0);
        REQUIRE(ret == VACCEL_OK);
        ret = vaccel_fpga_arraycopy(&sess, A, B, len_A);
        float B_expected[] = {1,2,3,4,5};


        REQUIRE(vaccel_sess_free(&sess) == VACCEL_OK);
        REQUIRE(ret != VACCEL_ENOTSUP);
        
        REQUIRE(std::equal(B, B + len_B, B_expected));
    }

}