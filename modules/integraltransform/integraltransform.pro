TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = integraltransformD

INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

SOURCES += \
    src/VO_WindowFunc.cpp \
    src/VO_Symlets.cpp \
    src/VO_STFT.cpp \
    src/VO_ReverseBiorthogonal.cpp \
    src/VO_Haar.cpp \
    src/VO_Gauss.cpp \
    src/VO_Gabor.cpp \
    src/VO_DiscreteFIRMeyer.cpp \
    src/VO_Daubechies.cpp \
    src/VO_Coiflets.cpp \
    src/VO_CohenDaubechiesFeauveau.cpp

HEADERS += \
    include/VO_WindowFunc.h \
    include/VO_Symlets.h \
    include/VO_STFT.h \
    include/VO_ReverseBiorthogonal.h \
    include/VO_IntegralTransform.h \
    include/VO_Haar.h \
    include/VO_Gauss.h \
    include/VO_Gabor.h \
    include/VO_DiscreteWavelet.h \
    include/VO_DiscreteFIRMeyer.h \
    include/VO_Daubechies.h \
    include/VO_Coiflets.h \
    include/VO_CohenDaubechiesFeauveau.h

