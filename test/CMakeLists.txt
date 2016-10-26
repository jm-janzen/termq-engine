
include_directories(${TEST_SOURCE_DIR}/src)

#add_executable(Test test.cpp)
add_executable(Test_vec2ui test_vec2ui.cpp)
target_link_libraries(Test_vec2ui
    gtest
    pthread
)

add_executable(Test_entity test_entity.cpp)
target_link_libraries(Test_entity
    TERMQ_LIB
    gtest
    pthread
    ${NCURSES_LIBRARIES}
)

