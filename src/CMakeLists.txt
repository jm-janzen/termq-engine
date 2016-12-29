
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Assign all source files recursively to `lib_src'
file(GLOB_RECURSE lib_src *.cpp *.h)

# Except main and cmake
list(REMOVE_ITEM lib_src main.cpp)

# Print lib_src list for debugging
message("Adding library source files:")
foreach(source_file ${lib_src})
    #message("\t" ${source_file})
endforeach(source_file)

# Finally add them
add_library(TERMQ_LIB
    ${lib_src}
)

# Add library target `termq'
add_library(termq ${lib_src})
target_link_libraries(termq PRIVATE ${NCURSES_LIBRARIES})

