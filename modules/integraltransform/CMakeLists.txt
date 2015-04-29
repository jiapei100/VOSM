include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set library source
set(LIB_SRC src/VO_CohenDaubechiesFeauveau.cpp src/VO_Gabor.cpp src/VO_STFT.cpp src/VO_Coiflets.cpp src/VO_Gauss.cpp src/VO_Symlets.cpp src/VO_Daubechies.cpp src/VO_Haar.cpp src/VO_WindowFunc.cpp src/VO_DiscreteFIRMeyer.cpp src/VO_ReverseBiorthogonal.cpp)

# Generate shared library
add_library(integraltransform_shared SHARED ${LIB_SRC} )
set_target_properties(integraltransform_shared PROPERTIES OUTPUT_NAME "vosm_integraltransform")
get_target_property(OUTPUT_NAME integraltransform_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" $(OUTPUT_NAME))

