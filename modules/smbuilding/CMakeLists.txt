include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../common/include" "${CMAKE_CURRENT_SOURCE_DIR}/../cvcommon/include" "${CMAKE_CURRENT_SOURCE_DIR}/../integraltransform/include" "${CMAKE_CURRENT_SOURCE_DIR}/../featureextraction/include")

# Set library source
set(LIB_SRC src/VO_AAMBasic.cpp src/VO_FeatureModel.cpp src/VO_AAMForwardIA.cpp src/VO_Point2DDistributionModel.cpp src/VO_AAMInverseIA.cpp src/VO_Profile.cpp src/VO_AFM.cpp src/VO_Shape2DInfo.cpp src/VO_ASMLTCs.cpp src/VO_Shape.cpp src/VO_ASMNDProfiles.cpp src/VO_ShapeFace.cpp src/VO_AXM.cpp  src/VO_ShapeModel.cpp src/VO_Edge.cpp src/VO_Texture.cpp src/VO_Ellipse.cpp src/VO_TextureModel.cpp src/VO_FacePart.cpp src/VO_Triangle2DStructure.cpp src/VO_FaceParts.cpp src/VO_WarpingPoint.cpp )

# Generate shared library
add_library(smbuilding_shared SHARED ${LIB_SRC} )
set_target_properties(smbuilding_shared PROPERTIES OUTPUT_NAME "vosm_smbuilding")
get_target_property(OUTPUT_NAME smbuilding_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" ${OUTPUT_NAME})

file(GLOB INSTALL_HEADERS
    "include/*.h"
)
install(TARGETS smbuilding_shared DESTINATION lib)
install(FILES ${INSTALL_HEADERS} DESTINATION include/vosm)
