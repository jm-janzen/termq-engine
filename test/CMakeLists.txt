project(test_termq)

#file(GLOB_RECURSE test_SOURCES "../src/*.cpp")
#file(GLOB_RECURSE test_HEADERS "../src/*.h")
file(GLOB_RECURSE test_SOURCES "*.cpp")
file(GLOB_RECURSE test_HEADERS "*.h")
#message("TEST SOURCES:" ${test_SOURCES})
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#add_executable(test_termq ${test_SOURCES})
#target_link_libraries(test_termq ${GTEST_LIBRARIES} ${NCURSES_LIBRARIES} pthread)
target_link_libraries(test_termq ${GTEST_LIBRARIES} ${NCURSES_LIBRARIES} ${termq_LIBRARIES} pthread)

#add_library(test_termq ${test_SOURCES})
add_executable(test_termq ${test_SOURCES})
target_include_directories(test_termq PUBLIC include)

