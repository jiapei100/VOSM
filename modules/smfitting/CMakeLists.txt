include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../common/include" "${CMAKE_CURRENT_SOURCE_DIR}/../cvcommon/include" "${CMAKE_CURRENT_SOURCE_DIR}/../integraltransform/include" "${CMAKE_CURRENT_SOURCE_DIR}/../featureextraction/include" "${CMAKE_CURRENT_SOURCE_DIR}/../smbuilding/include")


# Set library source
set(LIB_SRC src/VO_Fitting2DSM.cpp src/VO_FittingAFM.cpp src/VO_FittingAAMBasic.cpp src/VO_FittingASMLTCs.cpp src/VO_FittingAAMForwardIA.cpp src/VO_FittingASMNDProfiles.cpp src/VO_FittingAAMInverseIA.cpp )

# Generate shared library
add_library(smfitting_shared SHARED ${LIB_SRC} )
set_target_properties(smfitting_shared PROPERTIES OUTPUT_NAME "vosm_smfitting")
get_target_property(OUTPUT_NAME smfitting_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" ${OUTPUT_NAME})

file(GLOB INSTALL_HEADERS
    "include/*.h"
)
install(TARGETS smfitting_shared DESTINATION lib)
install(FILES ${INSTALL_HEADERS} DESTINATION include/vosm)
