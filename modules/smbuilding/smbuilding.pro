TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug | release): TARGET = smbuildingD

INCLUDEPATH += \
                include \
                ../common/include \
                ../cvcommon/include \
                ../featureextraction/include \
                ../integraltransform/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

SOURCES += \
    src/VO_WarpingPoint.cpp \
    src/VO_Triangle2DStructure.cpp \
    src/VO_TextureModel.cpp \
    src/VO_Texture.cpp \
    src/VO_ShapeModel.cpp \
    src/VO_ShapeFace.cpp \
    src/VO_Shape2DInfo.cpp \
    src/VO_Shape.cpp \
    src/VO_Profile.cpp \
    src/VO_Point2DDistributionModel.cpp \
    src/VO_FeatureModel.cpp \
    src/VO_FaceParts.cpp \
    src/VO_FacePart.cpp \
    src/VO_Ellipse.cpp \
    src/VO_Edge.cpp \
    src/VO_AXM.cpp \
    src/VO_ASMNDProfiles.cpp \
    src/VO_ASMLTCs.cpp \
    src/VO_AFM.cpp \
    src/VO_AAMInverseIA.cpp \
    src/VO_AAMForwardIA.cpp \
    src/VO_AAMBasic.cpp

HEADERS += \
    include/VO_WarpingPoint.h \
    include/VO_Triangle2DStructure.h \
    include/VO_Triangle2D.h \
    include/VO_TextureModel.h \
    include/VO_Texture.h \
    include/VO_ShapeModel.h \
    include/VO_ShapeFace.h \
    include/VO_Shape2DInfo.h \
    include/VO_Shape.h \
    include/VO_Profiles.h \
    include/VO_Profile.h \
    include/VO_Point2DDistributionModel.h \
    include/VO_FeatureModel.h \
    include/VO_FaceParts.h \
    include/VO_FacePart.h \
    include/VO_Ellipse.h \
    include/VO_Edge.h \
    include/VO_AXM.h \
    include/VO_ASMNDProfiles.h \
    include/VO_ASMLTCs.h \
    include/VO_AFM.h \
    include/VO_AAMInverseIA.h \
    include/VO_AAMForwardIA.h \
    include/VO_AAMBasic.h

