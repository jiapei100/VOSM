TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = ensembletrainingD

INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                ../featureextraction/include \
                ../integraltransform/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

SOURCES += \
    src/VO_AdditiveStrongerClassifier.cpp \
    src/VO_BaggingRandomForestClassifier.cpp \
    src/VO_BoostingCascadeClassifier.cpp \
    src/VO_BoostingSingleEnsembleClassifier.cpp \
    src/VO_WeakClassifier.cpp

HEADERS += \
    include/VO_AdditiveStrongerClassifier.h \
    include/VO_BaggingRandomForestClassifier.h \
    include/VO_BoostingCascadeClassifier.h \
    include/VO_BoostingSingleEnsembleClassifier.h \
    include/VO_WeakClassifier.h

