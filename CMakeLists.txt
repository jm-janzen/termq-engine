
cmake_minimum_required(VERSION 2.8.12)
project (termq)
enable_language(CXX)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

#option(USE_CLANG "build application with clang" ON)
#if(USE_CLANG)
#	set(CMAKE_CXX_COMPILER "clang++")

if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
include(FindPackageHandleStandardArgs)
find_path(NCURSES_INCLUDES
            NAMES ncurses.h
            PATHS
            ${INCLUDE_INSTALL_DIR}
)
find_library(NCURSES_LIBRARIES
                NAMES ncurses
                PATHS
                ${LIB_INSTALL_DIR}
)

find_package_handle_standard_args(ncurses DEFAULT_MSG NCURSES_INCLUDES NCURSES_LIBRARIES)

if(NCURSES_FOUND)
    message(STATUS "Found ncurses: ${NCURSES_LIBRARIES}")
    message(STATUS "Found c++11 compiler: ${CMAKE_CXX_COMPILER}")
else(NCURSES_FOUND)
    message(FATAL_ERROR "Could not find ncurses")
endif(NCURSES_FOUND)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic-errors -Wno-unused-variable" )

include(ExternalProject)
ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
    -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
    -Dgtest_force_shared_crt=${GTEST_FORCE_SHARED_CRT}
    -Dgtest_disable_pthreads=${GTEST_DISABLE_PTHREADS}
    -DBUILD_GTEST=ON
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    # Disable install step
    INSTALL_COMMAND ""
    )
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(src)

add_subdirectory(test)
enable_testing()

add_test(TEST_VEC2UI test/Test_vec2ui)
add_test(TEST_ENTITY test/Test_entity)
