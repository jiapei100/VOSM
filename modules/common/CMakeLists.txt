include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set library source
set(LIB_SRC src/VO_ScanFilesInDir.cpp)

# Generate shared library
add_library(common_shared SHARED ${LIB_SRC} )
set_target_properties(common_shared PROPERTIES OUTPUT_NAME "vosm_common")
get_target_property(OUTPUT_NAME common_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" $(OUTPUT_NAME))

