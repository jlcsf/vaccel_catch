Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)
# file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.h")
# file(GLOB HEADER_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/src/include/*.h")
file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}" )
file(GLOB HEADER_INCLUDE_FILES "${CMAKE_SOURCE_DIR}")

set(include_dirs
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/include
)




add_executable(tests "${CMAKE_SOURCE_DIR}/test/test.cpp")
target_compile_options(tests PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain gcov --coverage)



# set(ENV{VACCEL_BACKENDS} "${CMAKE_BINARY_DIR}/plugins/noop/libvaccel-noop.so")

# if (EXISTS $ENV{VACCEL_BACKENDS})
#     message("VACCEL_BACKENDS points to an existing file: $ENV{VACCEL_BACKENDS}")
# else ()
#     message(FATAL_ERROR "VACCEL_BACKENDS does not point to an existing file.")
# endif ()

add_executable(test_fpga "${CMAKE_SOURCE_DIR}/test/test_fpga.cpp" "${PROJECT_SOURCE_DIR}/src/ops/fpga.c")
target_include_directories(test_fpga
    PRIVATE
        ${include_dirs}
        ${CMAKE_SOURCE_DIR}/src/ops
        fff
)
target_compile_options(test_fpga PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
target_link_libraries(test_fpga PRIVATE Catch2::Catch2WithMain vaccel vaccel-noop gcov --coverage)

add_executable(test_plugins test_plugin.cpp "${PROJECT_SOURCE_DIR}/src/plugin.c")
target_include_directories(test_plugins
    PRIVATE
        ${include_dirs}
        fff
)
target_compile_options(test_plugins PUBLIC -Wall -Wextra --coverage -lgcov)
target_link_libraries(test_plugins Catch2::Catch2WithMain vaccel gcov --coverage)

add_executable(test_session "${CMAKE_SOURCE_DIR}/test/test_session.cpp")
target_include_directories(test_session
    PRIVATE
        ${include_dirs}
        ../fff
)
target_compile_options(test_session PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
target_link_libraries(test_session PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

add_executable(test_resource "${CMAKE_SOURCE_DIR}/test/test_resource.cpp")
target_include_directories(test_resource
    PRIVATE
        ${include_dirs}
        ../fff
)
target_compile_options(test_resource PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov) 
target_link_libraries(test_resource PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

add_executable(test_misc "${CMAKE_SOURCE_DIR}/test/test_misc.cpp")
target_include_directories(test_misc
    PRIVATE
        ${include_dirs}
        ../fff
)
target_compile_options(test_misc PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
target_link_libraries(test_misc PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

add_executable(test_id_pool "${CMAKE_SOURCE_DIR}/test/test_id_pool.cpp")
target_include_directories(test_id_pool
    PRIVATE
        ${include_dirs}
        ../fff
)
target_compile_options(test_id_pool PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
target_link_libraries(test_id_pool PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

add_executable(test_vaccel "${CMAKE_SOURCE_DIR}/test/test_vaccel.cpp")
target_include_directories(test_vaccel
    PRIVATE
        ${include_dirs}
        ../fff
)
target_compile_options(test_vaccel PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
target_link_libraries(test_vaccel PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)


add_executable(test_log "${CMAKE_SOURCE_DIR}/test/test_log.cpp")
target_include_directories(test_log
    PRIVATE
        ${include_dirs}
        ../fff
)
target_compile_options(test_log PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
target_link_libraries(test_log PRIVATE Catch2::Catch2WithMain vaccel vaccel-noop gcov --coverage)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/_deps/catch2-src/extras")
include(CTest)
include(Catch)


enable_testing()

# Set the environment variable for the tests

add_test(NAME basic_test COMMAND tests)
add_test(NAME test_log COMMAND test_log)
add_test(NAME test_vaccel COMMAND test_vaccel)
add_test(NAME test_id_pool COMMAND test_id_pool)
add_test(NAME test_misc COMMAND test_misc)
add_test(NAME test_resource COMMAND test_resource)
add_test(NAME test_session COMMAND test_session)
add_test(NAME test_plugins COMMAND test_plugins)
add_test(NAME test_fpga COMMAND test_fpga)

set_tests_properties(
    test_fpga test_vaccel
    PROPERTIES
    ENVIRONMENT "VACCEL_DEBUG_LEVEL=4;VACCEL_BACKENDS=${CMAKE_BINARY_DIR}/plugins/noop/libvaccel-noop.so"
    # ENVIRONMENT "VACCEL_DEBUG_LEVEL=4"
)

# catch_discover_tests(tests)
# catch_discover_tests(test_log)
# catch_discover_tests(test_vaccel)
# catch_discover_tests(test_id_pool)
# catch_discover_tests(test_misc)
# catch_discover_tests(test_resource)
# catch_discover_tests(test_session)
# catch_discover_tests(test_plugins)

# catch_discover_tests(test_plugins PROPERTIES ENVIRONMENT VACCEL_DEBUG_LEVEL=4)

# catch_discover_tests(test_fpga)

# set_tests_properties(
#     test_plugins
#     PROPERTIES
#     ENVIRONMENT "VACCEL_DEBUG_LEVEL=4;VACCEL_BACKENDS=${CMAKE_BINARY_DIR}/plugins/noop/libvaccel-noop.so"
# )

