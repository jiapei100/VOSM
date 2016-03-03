if (BUILD_EXAMPLES)
    project(smbuilding_exe)

    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")
    endif()
    
	include_directories(
		"${CMAKE_SOURCE_DIR}/modules/smbuilding/include"
        "${CMAKE_SOURCE_DIR}/modules/cvcommon/include"
		"${CMAKE_SOURCE_DIR}/modules/common/include"
		"${CMAKE_SOURCE_DIR}/modules/featureextraction/include"
		"${CMAKE_SOURCE_DIR}/modules/integraltransform/include"
	)
    find_package(Boost COMPONENTS filesystem system regex REQUIRED)
    find_package(OpenCV REQUIRED)

    set(VOSM_LIB_DIR ${CMAKE_BINARY_DIR}/modules/)
    link_directories(${VOSM_LIB_DIR}/common/ ${VOSM_LIB_DIR}/smbuilding/ 
                     ${VOSM_LIB_DIR}/featureextraction/ ${VOSM_LIB_DIR}/integraltransform/ ${VOSM_LIB_DIR}/cvcommon/ )

    # ---------------------------------------------
    #      Define executable targets
    # ---------------------------------------------
    MACRO(VO_DEFINE_EXAMPLE name srcs)
        set(the_target "vo_${name}")
    	add_executable(${the_target} ${srcs})

		set_target_properties(${the_target} PROPERTIES
		    OUTPUT_NAME "vo_${name}"
		    PROJECT_LABEL "(EXAMPLE) vo_${name}")


    	target_link_libraries(${the_target}
            vosm_common vosm_smbuilding vosm_featureextraction vosm_integraltransform vosm_cvcommon 
			boost_regex boost_filesystem boost_system
			opencv_core opencv_flann opencv_imgproc opencv_highgui opencv_ml opencv_video opencv_objdetect
    	    opencv_features2d opencv_calib3d opencv_legacy opencv_contrib)

        if(WIN32)
            install(TARGETS ${the_target}
                RUNTIME DESTINATION "samples" COMPONENT main)
        endif()
		install(TARGETS ${the_target} RUNTIME DESTINATION bin COMPONENT main)
    ENDMACRO(VO_DEFINE_EXAMPLE)
    
    file(GLOB cpp_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c)
    
    foreach(sample_filename ${cpp_samples})
        get_filename_component(sample ${sample_filename} NAME_WE)
        VO_DEFINE_EXAMPLE(${sample}  ${sample_filename})
    endforeach()
endif(BUILD_EXAMPLES)

if (INSTALL_C_EXAMPLES AND NOT WIN32)
    
    file(GLOB C_SAMPLES *.h *.c *.cpp *.jpg *.png *.data makefile.* build_all.sh *.dsp *.cmd )
    install(FILES ${C_SAMPLES}
            DESTINATION share/vosm/samples
            PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
#	install(TARGETS ${sample}
#	        DESTINATION bin
#	        PERMISSIONS OWNER_ALL GROUP_ALL WORLD_ALL)
endif ()

