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
    LIBS += -L../SDK/Libraries/Win
    LIBS += -lXPLM -lXPWidgets
    LIBS += $$quote(C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib\SetupAPI.Lib)
    SOURCES += \
          ../hidapi-0.7.0/windows/hid.c
    TARGET = win.xpl
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


# Trying to give info that might be helpfull in Mac building
# I do not own a Mac so am depending on what I have read in forums
# You should also consider building with 10.6 SDK otherwise
# only poeple with 10.7 will be able to load your plugins.
# QMAKE_CXXFLAGS += -m32 -isysroot /Developer/SDKs/MacOSX10.6.sdk
# QMAKE_LFLAGS += -m32 -flat_namespace -undefined suppress  -isysroot /Developer/SDKs/MacOSX10.6.sdk
# I have read that this will also work
# QMAKE_CXXFLAGS += -arch i386 -isysroot /Developer/SDKs/MacOSX10.6.sdk
# QMAKE_LFLAGS += -arch i386 -flat_namespace -undefined suppress  -isysroot /Developer/SDKs/MacOSX10.6.sdk

# This is what my builder is using on 10.7
macx {
    DEFINES += APL=1 IBM=0 LIN=0
    TARGET = mac.xpl
    QMAKE_LFLAGS += -flat_namespace -undefined suppress
    SOURCES += \
          ../hidapi-0.7.0/mac/hid.c
    LIBS += -framework IOKit -framework CoreFoundation

    # Build for multiple architectures.
    # The following line is only needed to build universal on PPC architectures.
    # QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.4u.sdk
    # The following line defines for which architectures we build.
    CONFIG += x86
}

HEADERS += ../saitekpanels.h \
      ../nireader.h

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
