QT       += core gui widgets
CONFIG += c++14

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

TARGET = FaceChanger
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

MOC_DIR = moc
RCC_DIR = resources

SOURCES += \
    main.cpp \
    Application.cpp \
    ManagementLayer/ApplicationManager.cpp \
    ViewLayer/ApplicationView.cpp

HEADERS += \
    Application.h \
    ManagementLayer/ApplicationManager.h \
    ViewLayer/ApplicationView.h \
    ViewLayer/ApplicationViewPrivate.h
