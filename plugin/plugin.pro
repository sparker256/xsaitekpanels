# Shared library without any Qt functionality
TEMPLATE = lib
QT -= gui core

CONFIG += warn_on plugin release
CONFIG -= thread exceptions qt rtti debug

VERSION = 1.0.0

INCLUDEPATH += ../../SDK/CHeaders/XPLM
INCLUDEPATH += ../../SDK/CHeaders/Wrappers
INCLUDEPATH += ../../SDK/CHeaders/Widgets


# Defined to use X-Plane SDK 2.0 capabilities - no backward compatibility before 9.0
DEFINES += XPLM200

win32 {
    message(win32)
    CONFIG += dll    	
    DEFINES += APL=0 IBM=1 LIN=0
    INCLUDEPATH += ../../hidapi-0.8.0-rc1_Patched/hidapi
    SOURCES += ../../hidapi-0.8.0-rc1_Patched/windows/hid.c
    LIBS += -L../../SDK/Libraries/Win
    TARGET = win.xpl
    INCLUDEPATH += .
    LIBS +=  "-lsetupapi"
    QMAKE_DEL_FILE          = rm -f
    INCLUDEPATH += "../../WinSDK/Include"
    LIBS += -static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic

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
    INCLUDEPATH += ../../hidapi-0.8.0-rc1/hidapi
    SOURCES += ../../hidapi-0.8.0-rc1/linux/hid.c
    LIBS += `pkg-config libudev --libs`
    QMAKE_LFLAGS += -Wl,-rpath=./Resources/plugins/Xsaitekpanels/64
    QMAKE_RPATH=


}

macx {
    DEFINES += APL=1 IBM=0 LIN=0
    TARGET = mac.xpl
    QMAKE_LFLAGS += -F../../SDK/Libraries/Mac/ -framework XPWidgets -framework XPLM
    INCLUDEPATH += ../../hidapi-0.8.0-rc1/hidapi
    SOURCES += \
          ../../hidapi-0.8.0-rc1/mac/hid.c
    LIBS += -framework IOKit -framework CoreFoundation
}

HEADERS += ../src/saitekpanels.h \
      ../src/inireader.h

SOURCES += ../src/saitekpanels.cpp \
    ../src/radiopanels.cpp \
    ../src/radio1data.cpp \
    ../src/radio2data.cpp \
    ../src/radio3data.cpp \
    ../src/multipanel.cpp \
    ../src/multidata.cpp \
    ../src/switchpanel.cpp \
    ../src/switchdata.cpp \
    ../src/bippanel.cpp \
    ../src/inireader.cpp \
    ../src/readinifile.cpp

 OTHER_FILES += \
    ../src/xsaitekpanels.ini
