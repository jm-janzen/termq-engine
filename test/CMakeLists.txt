
file(GLOB_RECURSE test_SOURCES "../src/*.cpp")
file(GLOB_RECURSE test_HEADERS "../src/*.h")
message("TEST SOURCES:" ${test_SOURCES})
add_definitions(-std=c++11)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include(ExternalProject)

# Link runTests with what we want to test and the GTest and pthread library
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

add_executable(runTests ${test_SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

