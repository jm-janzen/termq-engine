
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Assign all source files recursively to `lib_src'
file(GLOB_RECURSE lib_src *.cpp)

# Except main and cmake
list(REMOVE_ITEM lib_src main.cpp)

file(GLOB_RECURSE lib_inc *.h) # TODO move all *.h to inc/*

if(TARGET termq_lib)  # Guard for multiple targets
    message("termq_lib is already defined")
else()

    # Finally add them
    add_library(termq_lib ${lib_src})

    target_link_libraries(termq_lib PRIVATE ${NCURSES_LIBRARIES})

endif()

