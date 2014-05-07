TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                ../integraltransform/include \
                ../featureextraction/include \
                ../smbuilding/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += \
        -L/usr/local/lib \
        -L/opt/vosm/lib

LIBS += \
        -lsmfittingD \
        -lsmbuildingD \
        -lfeatureextractionD \
        -lintegraltransformD \
        -lcvcommonD \
        -lcommonD \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_features2d \
        -lboost_filesystem \
        -lboost_regex \
        -lboost_system

SOURCES += \
    testsmbuilding.cpp

HEADERS += \
    smb.h

