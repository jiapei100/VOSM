TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                ../featureextraction/include \
                ../integraltransform/include \
                ../smbuilding/include \
                ../smfitting/include \
                ../comalgs/include \
                ../ensembletraining/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

LIBS += \
        -L/usr/local/lib \
        -L/opt/vosm/lib

LIBS += \
        -lsmfitting \
        -lsmbuilding \
        -lfeatureextraction \
        -lintegraltransform \
        -lcomalgs \
        -lensembletraining \
        -lcvcommon \
        -lcommon \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_features2d \
        -lopencv_objdetect \
        -lopencv_legacy \
        -lboost_filesystem \
        -lboost_regex \
        -lboost_system

SOURCES += \
    testsmfitting.cpp

HEADERS += \
    smf.h

