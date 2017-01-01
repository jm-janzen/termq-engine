
include_directories(${TEST_SOURCE_DIR}/src)

add_executable(Test_vec2ui test_vec2ui.cpp)
set_target_properties(termq_lib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Test_vec2ui
    gtest
    pthread
)

add_executable(Test_entity test_entity.cpp)
set_target_properties(termq_lib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Test_entity
    termq_lib
    gtest
    pthread
    ${NCURSES_LIBRARIES}
)

add_executable(Test_item test_item.cpp)
set_target_properties(termq_lib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Test_item
    termq_lib
    gtest
    pthread
    ${NCURSES_LIBRARIES}
)

