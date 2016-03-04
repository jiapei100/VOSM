include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../common/include" "${CMAKE_CURRENT_SOURCE_DIR}/../cvcommon/include"
"${CMAKE_CURRENT_SOURCE_DIR}/../ensembletraining/include" "${CMAKE_CURRENT_SOURCE_DIR}/../smbuilding/include")

# Set library source
set(LIB_SRC src/VO_Algs_Classification.cpp src/VO_Algs_FaceDetection.cpp src/VO_Algs_Tracking.cpp src/VO_Algs_Detection.cpp src/VO_Algs_Locating.cpp src/VO_Algs_Evaluation.cpp src/VO_Algs_Recognition.cpp)

# Generate shared library
add_library(comalgs_shared SHARED ${LIB_SRC})
set_target_properties(comalgs_shared PROPERTIES OUTPUT_NAME "vosm_comalgs")
get_target_property(OUTPUT_NAME comalgs_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" ${OUTPUT_NAME})

file(GLOB INSTALL_HEADERS
    "include/*.h"
)
install(TARGETS comalgs_shared DESTINATION lib)
install(FILES ${INSTALL_HEADERS} DESTINATION include/vosm)
