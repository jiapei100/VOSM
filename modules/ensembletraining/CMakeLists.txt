include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../utils/include" "${CMAKE_CURRENT_SOURCE_DIR}/../featureextraction/include")
set(deps opencv_core opencv_imgproc opencv_highgui)
define_vosm_module(ensembletraining vosm_utils vosm_featureextraction ${deps})
