TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = vo_commonD

INCLUDEPATH += \
                include \
                ../common/include \
                ../smbuilding/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

HEADERS += \
    include/VO_FaceKeyPoint.h \
    include/VO_FaceCompPos.h \
    include/VO_DetectionDBIO.h \
    include/VO_CVCommon.h \
    include/VO_AnnotationDBIO.h

SOURCES += \
    src/VO_DetectionDBIO.cpp \
    src/VO_AnnotationDBIO.cpp \
    src/VO_FaceKeyPoint.cpp \
    src/VO_FaceCompPos.cpp


