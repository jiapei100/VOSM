include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../common/include" "${CMAKE_CURRENT_SOURCE_DIR}/../smbuilding/include")

# Set library source
set(LIB_SRC src/VO_AnnotationDBIO.cpp src/VO_FaceCompPos.cpp src/VO_DetectionDBIO.cpp src/VO_FaceKeyPoint.cpp)

# Generate shared library
add_library(cvcommon_shared SHARED ${LIB_SRC} )
set_target_properties(cvcommon_shared PROPERTIES OUTPUT_NAME "vosm_cvcommon")
get_target_property(OUTPUT_NAME cvcommon_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" $(OUTPUT_NAME))

