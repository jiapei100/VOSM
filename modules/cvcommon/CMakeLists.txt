include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../common/include" "${CMAKE_CURRENT_SOURCE_DIR}/../smbuilding/include")
set(deps opencv_core opencv_imgproc opencv_highgui)
define_vosm_module(cvcommon vosm_common ${deps})
