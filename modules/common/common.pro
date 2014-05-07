TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = commonD

INCLUDEPATH += \
                include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

SOURCES += \
    src/VO_ScanFilesInDir.cpp

HEADERS += \
    include/VO_ScanFilesInDir.h \
    include/VO_Common.h \
    include/VO_BoostCommon.h


