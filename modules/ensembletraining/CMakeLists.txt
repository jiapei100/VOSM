include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../featureextraction/include")

# Set library source
set(LIB_SRC src/VO_AdditiveStrongerClassifier.cpp src/VO_BoostingSingleEnsembleClassifier.cpp src/VO_BaggingRandomForestClassifier.cpp src/VO_WeakClassifier.cpp src/VO_BoostingCascadeClassifier.cpp)

# Generate shared library
add_library(ensembletraining_shared SHARED ${LIB_SRC} )
set_target_properties(ensembletraining_shared PROPERTIES OUTPUT_NAME "vosm_ensembletraining")
get_target_property(OUTPUT_NAME ensembletraining_shared OUTPUT_NAME)
message(STATUS "Shared library outname:" ${OUTPUT_NAME})

file(GLOB INSTALL_HEADERS
    "include/*.h"
)
install(TARGETS ensembletraining_shared DESTINATION lib/vosm)
install(FILES ${INSTALL_HEADERS} DESTINATION include/vosm)
