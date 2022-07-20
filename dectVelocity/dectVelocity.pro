#-------------------------------------------------
#
# Project created by QtCreator 2022-07-08T09:59:24
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dectVelocity
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    camclass.cpp \
    dealclass.cpp \
    sliderclick.cpp \
    control.cpp

HEADERS += \
        widget.h \
    camclass.h \
    dealclass.h \
    sliderclick.h \
    control.h

FORMS += \
        widget.ui

INCLUDEPATH += /usr/local/include\
               /usr/local/include/opencv\
               /usr/local/include/opencv2
LIBS += /usr/local/lib/libopencv_core.so
LIBS += /usr/local/lib/libopencv_highgui.so
LIBS += /usr/local/lib/libopencv_video.so
LIBS += /usr/local/lib/libopencv_videoio.so
LIBS += /usr/local/lib/libopencv_imgproc.so
LIBS += /usr/local/lib/libopencv_highgui.so
LIBS += /usr/local/lib/libopencv_imgcodecs.so

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ironbk.qrc
