
cmake_minimum_required(VERSION 2.8.12)
project (termq)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

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
else(NCURSES_FOUND)
    message(FATAL_ERROR "Could not find ncurses")
endif(NCURSES_FOUND)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic-errors" )

add_subdirectory(src)
