TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = comalgsD


INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                ../integraltransform/include \
                ../featureextraction/include \
                ../ensembletraining/include \
                ../smbuilding/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

SOURCES += \
    src/VO_Algs_Classification.cpp \
    src/VO_Algs_Detection.cpp \
    src/VO_Algs_Evaluation.cpp \
    src/VO_Algs_FaceDetection.cpp \
    src/VO_Algs_Localization.cpp \
    src/VO_Algs_Recognition.cpp \
    src/VO_Algs_Tracking.cpp

HEADERS += \
    include/VO_Algs_Classification.h \
    include/VO_Algs_Detection.h \
    include/VO_Algs_Evaluation.h \
    include/VO_Algs_FaceDetection.h \
    include/VO_Algs_Localization.h \
    include/VO_Algs_Recognition.h \
    include/VO_Algs_Tracking.h

