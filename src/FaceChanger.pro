QT     += core gui widgets
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

### opencv
!android: {
    OPENCV_CHECK = $$(OPENCV_SDK_DIR)
    isEmpty(OPENCV_CHECK) {
        error("Let OPENCV_SDK_DIR point to the opencv-sdk, using: v4.1.2")
    }
    INCLUDEPATH += $$(OPENCV_SDK_DIR)/include
    LIBS += -L$$(OPENCV_SDK_DIR)/x64/mingw/lib
    LIBS += -L$$(OPENCV_SDK_DIR)/x86/mingw/lib
    LIBS += \
        -lopencv_core412        \
        -lopencv_highgui412     \
        -lopencv_imgcodecs412   \
        -lopencv_imgproc412     \
        -lopencv_features2d412  \
        -lopencv_calib3d412     \
        -lopencv_objdetect412   \
        -lopencv_videoio412
} else {
    OPENCV_CHECK = $$(OPENCV_ANDROID)
    isEmpty(OPENCV_CHECK) {
        error("Let OPENCV_ANDROID point to the opencv-android-sdk, using: v4.1.2")
    }
    INCLUDEPATH += $$(OPENCV_ANDROID)/sdk/native/jni/include
    LIBS += \
        -L$$(OPENCV_ANDROID)/sdk/native/libs/$$ANDROID_TARGET_ARCH \
        -L$$(OPENCV_ANDROID)/sdk/native/3rdparty/libs/$$ANDROID_TARGET_ARCH \
        -llibtiff \
        -llibjpeg-turbo \
        -llibjasper \
        -llibpng \
        -lIlmImf \
        -ltbb \
        -lopencv_java4 \
}


SOURCES += \
    main.cpp \
    Application.cpp \
    BusinessLayer/Effects/NoEffectImage.cpp \
    BusinessLayer/FaceImage.cpp \
    BusinessLayer/FaceImageCreator.cpp \
    BusinessLayer/FrameCreator.cpp \
    BusinessLayer/Effects/SimpleCirclesEffectImage.cpp \
    ManagementLayer/ApplicationManager.cpp \
    ViewLayer/ApplicationView.cpp \
    _utils/Widgets/ItemsSlider/ItemsSlider.cpp \
    _utils/Helpers/CVHelper.cpp \
    _utils/Helpers/UIHelper.cpp


HEADERS += \
    Application.h \
    BusinessLayer/EffectImage.h \
    BusinessLayer/Effects/NoEffectImage.h \
    BusinessLayer/FaceImage.h \
    BusinessLayer/FaceImageCreator.h \
    BusinessLayer/FrameCreator.h \
    BusinessLayer/IconItem.h \
    BusinessLayer/Effects/SimpleCirclesEffectImage.h \
    ManagementLayer/ApplicationManager.h \
    ViewLayer/ApplicationView.h \
    ViewLayer/ApplicationViewPrivate.h \
    _utils/Widgets/ItemsSlider/ItemsSlider.h \
    _utils/Helpers/CVHelper.h \
    _utils/Helpers/UIHelper.h


RESOURCES += \
    Resources/resources.qrc
