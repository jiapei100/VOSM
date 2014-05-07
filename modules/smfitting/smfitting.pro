TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = smfittingD

INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                ../featureextraction/include \
                ../integraltransform/include \
                ../smbuilding/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

HEADERS += \
    include/VO_FittingASMNDProfiles.h \
    include/VO_FittingASMLTCs.h \
    include/VO_FittingAFM.h \
    include/VO_FittingAAMInverseIA.h \
    include/VO_FittingAAMForwardIA.h \
    include/VO_FittingAAMBasic.h \
    include/VO_Fitting2DSM.h

SOURCES += \
    src/VO_FittingASMNDProfiles.cpp \
    src/VO_FittingASMLTCs.cpp \
    src/VO_FittingAFM.cpp \
    src/VO_FittingAAMInverseIA.cpp \
    src/VO_FittingAAMForwardIA.cpp \
    src/VO_FittingAAMBasic.cpp \
    src/VO_Fitting2DSM.cpp
