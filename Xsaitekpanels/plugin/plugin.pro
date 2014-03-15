# Shared library without any Qt functionality
TEMPLATE = lib
QT -= gui core

CONFIG += warn_on plugin release
CONFIG -= thread exceptions qt rtti debug

VERSION = 1.0.0

INCLUDEPATH += ../../SDK/CHeaders/XPLM
INCLUDEPATH += ../../SDK/CHeaders/Wrappers
INCLUDEPATH += ../../SDK/CHeaders/Widgets
INCLUDEPATH += ../../hidapi-0.8.0-rc1/hidapi

# Defined to use X-Plane SDK 2.0 capabilities - no backward compatibility before 9.0
DEFINES += XPLM200

win32 {
    message(win32)
    CONFIG += dll    	
    DEFINES += APL=0 IBM=1 LIN=0
    SOURCES += ../../hidapi-0.8.0-rc1/windows/hid.c
    LIBS += -L../../SDK/Libraries/Win
    TARGET = win.xpl
    INCLUDEPATH += .
    LIBS +=  "-lsetupapi"
    # LIBS +=  "-lSetupAPI"
}

win32:isEmpty(CROSS_COMPILE){
    message(win32nocross)
    LIBS += -lXPLM -lXPWidgets
    LIBS += "-LD:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib"
    INCLUDEPATH += D:/gnu/include
    INCLUDEPATH += "D:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Include"
    INCLUDEPATH += .
}

win32:!isEmpty(CROSS_COMPILE){
    message(win32cross)
    QMAKE_YACC = yacc
    QMAKE_YACCFLAGS_MANGLE  += -p $base -b $base
    QMAKE_YACC_HEADER       = $base.tab.h
    QMAKE_YACC_SOURCE       = $base.tab.c
    QMAKE_DEL_FILE          = rm -f
    INCLUDEPATH += "../../WinSDK/Include"
    LIBS += -static-libstdc++ -static-libgcc
}

win32:contains(CROSS_COMPILE, x86_64-w64-mingw32-){
    message(win32cross64)
    LIBS += -L"../../WinSDK/Lib/x64"
    LIBS += -lXPLM_64 -lXPWidgets_64
}

win32:contains(CROSS_COMPILE, i686-w64-mingw32-){
    message(win32cross32)
    LIBS += -L"../../WinSDK/Lib"
    LIBS += -lXPLM -lXPWidgets
    DEFINES += __MIDL_user_allocate_free_DEFINED__
}

unix:!macx {
    DEFINES += APL=0 IBM=0 LIN=1
    TARGET = lin.xpl
    # WARNING! This requires the latest version of the X-SDK !!!!
    QMAKE_CXXFLAGS += -fvisibility=hidden
    SOURCES += \
          ../../hidapi-0.8.0-rc1/linux/hid.c
    LIBS += `pkg-config libudev --libs`

}

macx {
    DEFINES += APL=1 IBM=0 LIN=0
    TARGET = mac.xpl
    QMAKE_LFLAGS += -F../../SDK/Libraries/Mac/ -framework XPWidgets -framework XPLM

    SOURCES += \
          ../../hidapi-0.8.0-rc1/mac/hid.c
    LIBS += -framework IOKit -framework CoreFoundation
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
