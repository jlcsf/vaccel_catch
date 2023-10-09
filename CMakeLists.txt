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
# if (ENABLE_TESTS)
# 	## Download GoogleTest framework
# 	configure_file(
# 		CMakeLists.txt.in
# 		googletest-download/CMakeLists.txt)
# 	execute_process(
# 		COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
# 		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
# 	execute_process(
# 		COMMAND ${CMAKE_COMMAND} --build .
# 		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

# 	# Add GTest directly to our build. This adds the targets:
# 	# gtest, gtest_main, gmock, and gmock_main
# 	add_subdirectory(
# 		${CMAKE_BINARY_DIR}/googletest-src
# 		${CMAKE_BINARY_DIR}/googletest-build)

# 	enable_testing()
# 	add_subdirectory(test)
# endif (ENABLE_TESTS)
if (ENABLE_TESTS)
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

add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain gcov)

include_directories(src)
include_directories(src/include)
include_directories(src/include/ops)
include_directories(fff)


add_executable(test_plugins tests/test_plugin.cpp)
target_compile_options(test_plugins PRIVATE -Wall -Wextra -g -ggdb -coverage)
target_link_libraries(test_plugins PRIVATE Catch2::Catch2WithMain vaccel gcov)

add_executable(test_session tests/test_session.cpp)
target_compile_options(test_session PRIVATE -Wall -Wextra -g -ggdb -coverage)
target_link_libraries(test_session PRIVATE Catch2::Catch2WithMain vaccel gcov)

add_executable(test_misc tests/test_misc.cpp)
target_compile_options(test_misc PRIVATE -Wall -Wextra -g -ggdb -coverage)
target_link_libraries(test_misc PRIVATE Catch2::Catch2WithMain vaccel gcov)

add_executable(test_fpga tests/test_fpga.cpp)
target_compile_options(test_fpga PRIVATE -Wall -Wextra -g -ggdb)
target_link_libraries(test_fpga PRIVATE Catch2::Catch2WithMain vaccel vaccel-noop)

endif (ENABLE_TESTS)

set(CPACK_PACKAGE_NAME vaccel)
set(CPACK_PACKAGE_CONTACT "Anastassios Nanos <ananos@nubificus.co.uk>")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})


include(CPack)
