#-------------------------------------------------
#
# Project created by Nordine Sebkhi
#
#-------------------------------------------------

QT      += core gui printsupport widgets serialport multimedia multimediawidgets
CONFIG  += console static

TARGET = TTS_NEU
TEMPLATE = app


SOURCES += main.cpp\
        TTS_GUI.cpp \
    qcustomplot.cpp \
    pugixml.cpp \
    mojoserialport.cpp \
    Magnet.cpp \
    Sensor.cpp \
    ReadSensors.cpp \
    sensordisplay.cpp \
    Localization.cpp \
    asa047.cpp

HEADERS  += TTS_GUI.h \
    qcustomplot.h \
    common.h \
    pugixml.hpp \
    pugiconfig.hpp \
    CImg.h \
    mojoserialport.h \
    Magnet.h \
    Sensor.h \
    ReadSensors.h \
    sensordisplay.h \
    Localization.h \
    asa047.hpp

FORMS    += \
    TTS_GUI.ui \
    sensordisplay.ui

LIBS += -lAdvapi32 -lgdi32 -luser32 -lshell32

# Boost Libraries
INCLUDEPATH += "C:/dev/Boost/boost_1_59_0"  # Needed for the boost/... includes
DEPENDPATH  += "C:/dev/Boost/boost_1_59_0/stage/lib"
LIBS += -LC:/dev/Boost/boost_1_59_0/stage/lib
#unix|win32: LIBS += -L$$PWD/../../../../../../dev/boost_1_57_0-0/lib64-msvc-12.0/ -lboost_system-vc120-mt-gd-1_57
#unix|win32: LIBS += -L$$PWD/../../../../../../dev/boost_1_57_0-0/lib64-msvc-12.0/ -lboost_regex-vc120-mt-gd-1_57

# OPEN CV
INCLUDEPATH += "C:/dev/OpenCV/opencv_0/Source/build/include"
DEPENDPATH  += "C:/dev/OpenCV/opencv_0/Source/build/x86/vc12/staticlib"
LIBS += -LC:/dev/OpenCV/opencv_0/Source/build/x86/vc12/staticlib










