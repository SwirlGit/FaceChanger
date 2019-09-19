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

SOURCES += \
    main.cpp \
    Application.cpp \
    BusinessLayer/EffectImage.cpp \
    BusinessLayer/FaceImage.cpp \
    ManagementLayer/ApplicationManager.cpp \
    ViewLayer/ApplicationView.cpp \
    _utils/Widgets/ItemsSlider/ItemsSlider.cpp

HEADERS += \
    Application.h \
    BusinessLayer/EffectImage.h \
    BusinessLayer/FaceImage.h \
    ManagementLayer/ApplicationManager.h \
    ViewLayer/ApplicationView.h \
    ViewLayer/ApplicationViewPrivate.h \
    _utils/Widgets/ItemsSlider/ItemsSlider.h
