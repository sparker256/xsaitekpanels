# Shared library without any Qt functionality
TEMPLATE = lib
QT -= gui core

CONFIG += warn_on plugin release
CONFIG -= thread exceptions qt rtti debug

VERSION = 1.0.0

INCLUDEPATH += ../../SDK/CHeaders/XPLM
INCLUDEPATH += ../../SDK/CHeaders/Wrappers
INCLUDEPATH += ../../SDK/CHeaders/Widgets
INCLUDEPATH += ../../hidapi-0.7.0/hidapi

# Defined to use X-Plane SDK 2.0 capabilities - no backward compatibility before 9.0
DEFINES += XPLM200

win32 {
    DEFINES += APL=0 IBM=1 LIN=0
    LIBS += -L../../SDK/Libraries/Win
    LIBS += -lXPLM -lXPWidgets
    TARGET = win.xpl
    LIBS += "-LD:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib"
    LIBS +=  "-lSetupAPI"
    INCLUDEPATH += D:/gnu/include
    INCLUDEPATH += "D:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Include"
    INCLUDEPATH += .
    SOURCES += \
          ../../hidapi-0.7.0/windows/hid.c

}

unix:!macx {
    DEFINES += APL=0 IBM=0 LIN=1
    TARGET = lin.xpl
    # WARNING! This requires the latest version of the X-SDK !!!!
    QMAKE_CXXFLAGS += -fvisibility=hidden
    SOURCES += \
          ../../hidapi-0.7.0/linux/hid.c
    LIBS += `pkg-config libudev --libs`

}

macx {
    DEFINES += APL=1 IBM=0 LIN=0
    TARGET = mac.xpl
    QMAKE_LFLAGS += -F../../SDK/Libraries/Mac/ -framework XPWidgets -framework XPLM
    SOURCES += \
          ../../hidapi-0.7.0/mac/hid.c
    LIBS += -framework IOKit -framework CoreFoundation
}

HEADERS += ../saitekpanels.h \
      ../inireader.h

SOURCES += ../saitekpanels.cpp\
    ../radiopanels.cpp \
    ../radio1data.cpp \
    ../radio2data.cpp \
    ../multipanel.cpp \
    ../multidata.cpp \
    ../switchpanel.cpp \
    ../switchdata.cpp \
    ../bippanel.cpp \
    ../inireader.cpp \
    ../readinifile.cpp


OTHER_FILES += \
    ../xsaitekpanels.ini
