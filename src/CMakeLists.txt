
# Assign all source files recursively to `lib_src'
file(GLOB_RECURSE lib_src *.cpp)

# Except main and cmake
list(REMOVE_ITEM lib_src main.cpp)

file(GLOB_RECURSE lib_inc *.h) # TODO move all *.h to inc/*

if(TARGET termq_lib)  # Guard for multiple targets
    message("termq_lib is already defined")
else()

    include_directories("${PROJECT_SOURCE_DIR}/inc")

    add_library(termq_lib ${lib_src} ${lib_inc})

    target_link_libraries(termq_lib PRIVATE ${NCURSES_LIBRARIES})

endif()

