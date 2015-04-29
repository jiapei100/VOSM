include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../integraltransform/include")

# Set library source
set(LIB_SRC src/VO_DaubechiesFeatures.cpp src/VO_GaborFeatures.cpp src/VO_LBPFeatures.cpp src/VO_DirectFeatures.cpp src/VO_HaarFeatures.cpp)

# Generate shared library
add_library(featureextraction_shared SHARED ${LIB_SRC} )
set_target_properties(featureextraction_shared PROPERTIES OUTPUT_NAME "vosm_featureextraction")
get_target_property(OUTPUT_NAME featureextraction_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" $(OUTPUT_NAME))

