
file(GLOB_RECURSE termq_SOURCES "*.cpp")
file(GLOB_RECURSE termq_HEADERS "*.h")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(termq ${termq_SOURCES})
target_link_libraries(termq PRIVATE ${NCURSES_LIBRARIES})
