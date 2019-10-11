QT       += core gui widgets
CONFIG += c++14

!android: {
    QMAKE_CXXFLAGS_DEBUG += -pg
    QMAKE_LFLAGS_DEBUG += -pg
}

TARGET = FaceChanger
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

MOC_DIR = moc
RCC_DIR = resources

INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

LIBS += -L$$(OPENCV_SDK_DIR)/x86/mingw/lib \
        -lopencv_core412        \
        -lopencv_highgui412     \
        -lopencv_imgcodecs412   \
        -lopencv_imgproc412     \
        -lopencv_features2d412  \
        -lopencv_calib3d412     \
        -lopencv_objdetect412

SOURCES += \
    main.cpp \
    Application.cpp \
    BusinessLayer/EffectImage.cpp \
    BusinessLayer/FaceImage.cpp \
    BusinessLayer/FaceImageCreator.cpp \
    ManagementLayer/ApplicationManager.cpp \
    ViewLayer/ApplicationView.cpp \
    _utils/Widgets/ItemsSlider/ItemsSlider.cpp \
    _utils/Helpers/CVHelper.cpp


HEADERS += \
    Application.h \
    BusinessLayer/EffectImage.h \
    BusinessLayer/FaceImage.h \
    BusinessLayer/FaceImageCreator.h \
    ManagementLayer/ApplicationManager.h \
    ViewLayer/ApplicationView.h \
    ViewLayer/ApplicationViewPrivate.h \
    _utils/Widgets/ItemsSlider/ItemsSlider.h \
    _utils/Helpers/CVHelper.h
