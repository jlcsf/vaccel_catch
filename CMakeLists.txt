cmake_minimum_required(VERSION 3.10)

project(vaccelrt
	VERSION 0.5.0
	DESCRIPTION "VaccelRT library"
	LANGUAGES C CXX)

# Configuration time options
option(BUILD_PLUGIN_EXEC "Build the exec plugin" OFF)
option(BUILD_PLUGIN_NOOP "Build the no-op debugging plugin" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)
option(ENABLE_TESTS "Enable testing" OFF)

# Export json with compile commands
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

# installation paths
include(GNUInstallDirs)

# Add CMake third-party dependencies to be built
add_subdirectory(third-party)

# Add include directories from third-party libraries
include_directories(
	#slog
	third-party/slog/src
)

add_subdirectory(src)
add_subdirectory(plugins)
add_subdirectory(python)

# if (BUILD_EXAMPLES)
# 	add_subdirectory(examples)
# endif (BUILD_EXAMPLES)

# tests

if (ENABLE_TESTS)
	enable_testing()
	add_subdirectory(test)
endif (ENABLE_TESTS)

# if (ENABLE_TESTS_LEGACY)

# Include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v3.4.0
# )

# FetchContent_MakeAvailable(Catch2)
# # file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.h")
# # file(GLOB HEADER_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/src/include/*.h")
# file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}" )
# file(GLOB HEADER_INCLUDE_FILES "${CMAKE_SOURCE_DIR}")



# add_executable(tests tests/test.cpp)
# target_compile_options(tests PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(tests PRIVATE Catch2::Catch2WithMain gcov --coverage)

# add_executable(test_plugins tests/test_plugin.cpp)
# target_include_directories(test_plugins
#     PRIVATE
#         third-party/slog/src
#         src
#         src/include
#         build
#         fff
# )
# target_compile_options(test_plugins PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(test_plugins PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

# add_executable(test_fpga tests/test_fpga.cpp)
# target_include_directories(test_fpga
#     PRIVATE
#         third-party/slog/src
#         src
#         src/include
#         src/include/ops
#         build
#         fff
# )
# target_compile_options(test_fpga PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(test_fpga PRIVATE Catch2::Catch2WithMain vaccel vaccel-noop gcov --coverage)

# add_executable(test_session tests/test_session.cpp)
# target_include_directories(test_session
#     PRIVATE
#         third-party/slog/src
#         src
#         src/include
#         build
#         fff 
# )
# target_compile_options(test_session PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(test_session PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

# add_executable(test_misc tests/test_misc.cpp)
# target_include_directories(test_misc
#     PRIVATE
#         third-party/slog/src
#         src/include
#         src
#         build
#         fff
# )
# target_compile_options(test_misc PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(test_misc PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

# add_executable(test_resource tests/test_resource.cpp)
# target_include_directories(test_resource
#     PRIVATE
#         third-party/slog/src
#         src
#         fff
# )
# target_compile_options(test_resource PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov) 
# target_link_libraries(test_resource PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

# add_executable(test_id_pool tests/test_id_pool.cpp)
# target_include_directories(test_id_pool
#     PRIVATE
#         third-party/slog/src
#         src
#         src/include
#         build
#         fff
# )
# target_compile_options(test_id_pool PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(test_id_pool PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)

# add_executable(test_vaccel tests/test_vaccel.cpp)
# target_include_directories(test_vaccel
#     PRIVATE
#         third-party/slog/src
#         src
#         src/include
#         build
#         fff
# )
# target_compile_options(test_vaccel PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(test_vaccel PRIVATE Catch2::Catch2WithMain vaccel gcov --coverage)


# add_executable(test_log tests/test_log.cpp)
# target_include_directories(test_log
#     PRIVATE
#         third-party/slog/src
#         src
#         src/include
#         src/include/ops
#         build
#         fff
# )
# target_compile_options(test_log PRIVATE -Wall -Wextra -g -ggdb --coverage -lgcov)
# target_link_libraries(test_log PRIVATE Catch2::Catch2WithMain vaccel vaccel-noop gcov --coverage)

# # list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/_deps/catch2-src/extras")
# # include(CTest)
# # include(Catch)
# # enable_testing()

# # add_test(NAME basic_test COMMAND tests)
# # add_test(NAME test_log COMMAND test_log)
# # add_test(NAME test_vaccel COMMAND test_vaccel)
# # add_test(NAME test_id_pool COMMAND test_id_pool)
# # add_test(NAME test_misc COMMAND test_misc)
# # add_test(NAME test_resource COMMAND test_resource)
# # add_test(NAME test_session COMMAND test_session)
# # add_test(NAME test_plugins COMMAND test_plugins)
# # add_test(NAME test_fpga COMMAND test_fpga)

# # set_tests_properties(
# #     test_fpga test_vaccel
# #     PROPERTIES
# #     ENVIRONMENT "VACCEL_DEBUG_LEVEL=4;VACCEL_BACKENDS=${CMAKE_BINARY_DIR}/plugins/noop/libvaccel-noop.so"
# # )

# # set_tests_properties(
# #     test_plugins
# #     PROPERTIES
# #     ENVIRONMENT "VACCEL_BACKENDS=${CMAKE_BINARY_DIR}/plugins/noop/libvaccel-noop.so"
# # )

# endif (ENABLE_TESTS_LEGACY)

set(CPACK_PACKAGE_NAME vaccel)
set(CPACK_PACKAGE_CONTACT "Anastassios Nanos <ananos@nubificus.co.uk>")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})


include(CPack)
