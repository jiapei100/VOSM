TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = vo_featureextractionD

INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                ../integraltransform/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

HEADERS += \
    include/VO_LBPFeatures.h \
    include/VO_HaarFeatures.h \
    include/VO_GaborFeatures.h \
    include/VO_Features.h \
    include/VO_DirectFeatures.h \
    include/VO_DaubechiesFeatures.h

SOURCES += \
    src/VO_LBPFeatures.cpp \
    src/VO_HaarFeatures.cpp \
    src/VO_GaborFeatures.cpp \
    src/VO_DirectFeatures.cpp \
    src/VO_DaubechiesFeatures.cpp
