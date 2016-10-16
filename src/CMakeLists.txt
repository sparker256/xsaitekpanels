cmake_minimum_required(VERSION 2.8.3)
project(plugin CXX)

SET(SRC bippanel.cpp inireader.cpp multipanel.cpp radio1data.cpp
    radio2data.cpp radio3data.cpp radiopanels.cpp readinifile.cpp
    saitekpanels.cpp switchdata.cpp switchpanel.cpp Dataref.cpp Log.cpp
    time.cpp Command.cpp)
SET(HDR inireader.h saitekpanels.h)

if(APPLE)
	SET(HIDAPI_SRC ../hidapi-0.8.0-rc1_Patched/mac/hid.c)
elseif(UNIX)
	SET(HIDAPI_SRC ../hidapi-0.8.0-rc1_Patched/linux/hid.c)
elseif(WIN32)
	SET(HIDAPI_SRC ../hidapi-0.8.0-rc1_Patched/windows/hid.c)
endif()

SET(ALL_SRC ${SRC} ${HIDAPI_SRC} ${HDR})
LIST(SORT ALL_SRC)

if(APPLE)
	add_executable(plugin ${ALL_SRC})
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
elseif(UNIX)
	add_library(plugin SHARED ${ALL_SRC})
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -ggdb3")
elseif(WIN32)
	add_library(plugin MODULE ${ALL_SRC})
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

#compiler flags
if(WIN32)
	set(CMAKE_CXX_FLAGS
	    "${CMAKE_CXX_FLAGS} -DCHECK_RESULT_USED=_Check_return_")
else()
	set(CMAKE_CXX_FLAGS
	    "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror --std=c++11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
	    -DCHECK_RESULT_USED=\"__attribute__ ((warn_unused_result))\"")
endif()

#libraries
if(UNIX)
	include_directories(plugin PUBLIC "../SDK/CHeaders/XPLM/"
	    "../SDK/CHeaders/Widgets/" "../SDK/CHeaders/Wrappers/"
	    "../hidapi-0.8.0-rc1_Patched/hidapi")
endif(UNIX)
if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch x86_64")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch x86_64")
	target_include_directories(plugin PUBLIC
	    "../hidapi-0.8.0-rc1_Patched/hidapi")
	find_library(IOKIT_FRAMEWORK IOKit)
	find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
	target_link_libraries(${PROJECT_NAME} ${COREFOUNDATION_FRAMEWORK}
	    ${IOKIT_FRAMEWORK})
endif(APPLE)
if(WIN32)
	target_include_directories(plugin PUBLIC "..\\SDK\\CHeaders\\XPLM"
	    "..\\SDK\\CHeaders\\Widgets" "..\\SDK\\CHeaders\\Wrappers"
	    "../hidapi-0.8.0-rc1_Patched/hidapi")
	target_include_directories(plugin_custom_dataref PUBLIC
	    "..\\SDK\\CHeaders\\XPLM" "..\\SDK\\CHeaders\\Widgets"
	    "..\\SDK\\CHeaders\\Wrappers")
endif(WIN32)

# X-Plane stuff
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DXPLM200=1 -DXPLM210=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DXPLM200=1 -DXPLM210=1")
if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=1 -DIBM=0 -DLIN=0")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DAPL=1 -DIBM=0 -DLIN=0")
elseif(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=0 -DIBM=0 -DLIN=1")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DAPL=0 -DIBM=0 -DLIN=1")
elseif(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=0 -DIBM=1 -DLIN=0 \
	    -D_CRT_SECURE_NO_WARNINGS /bigobj")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DAPL=0 -DIBM=1 -DLIN=0 \
	    -D_CRT_SECURE_NO_WARNINGS /bigobj")
endif()

#linking
link_libraries(m)
if(APPLE)
	set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ../SDK/Libraries/Mac/)
	FIND_LIBRARY(XPLM_LIBRARY XPLM ../SDK/Libraries/Mac/)
	FIND_LIBRARY(XPWIDGETS_LIBRARY XPWidgets ../SDK/Libraries/Mac/)
	target_link_libraries(plugin ${XPLM_LIBRARY} ${XPWIDGETS_LIBRARY})
elseif(UNIX)
	INCLUDE(FindPkgConfig)
	pkg_check_modules(UDEV REQUIRED libudev)
	include_directories(${UDEV_INCLUDE_DIRS})
	link_directories(${UDEV_LIBRARY_DIRS})
	target_link_libraries(plugin ${UDEV_LIBRARIES})	
elseif(WIN32)
	set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
	    "..\\SDK\\Libraries\\Win\\")
	FIND_LIBRARY(XPLM_LIBRARY XPLM_64
	    "..\\SDK\\Libraries\\Win\\")
	FIND_LIBRARY(XPWIDGETS_LIBRARY XPWidgets_64
	    "..\\SDK\\Libraries\\Win\\")
	target_link_libraries(plugin ${XPLM_LIBRARY}
	    ${XPWIDGETS_LIBRARY})
	target_link_libraries(plugin_custom_dataref
	    ${XPLM_LIBRARY} ${XPWIDGETS_LIBRARY})
endif()

#output
SET_TARGET_PROPERTIES(plugin PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(plugin PROPERTIES SUFFIX "")
if(APPLE)
	set(PLUGIN_OUTPUT_FILENAME "mac.xpl")
	SET_TARGET_PROPERTIES(plugin PROPERTIES LINK_FLAGS
	    "${CMAKE_SHARED_LINKER_FLAGS} -fPIC -fvisibility=hidden \
	    -bundle -framework OpenGL -framework Cocoa")
elseif(UNIX)
	set(PLUGIN_OUTPUT_FILENAME "lin.xpl")
	SET_TARGET_PROPERTIES(plugin PROPERTIES LINK_FLAGS
	    "${CMAKE_SHARED_LINKER_FLAGS} -rdynamic -nodefaultlibs \
	    -undefined_warning -fPIC -fvisibility=hidden")
elseif(WIN32)
	set(PLUGIN_OUTPUT_FILENAME "win.xpl")
endif()


set_target_properties(plugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/Xsaitekpanels" )
set_target_properties(plugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/Xsaitekpanels" )
set_target_properties(plugin PROPERTIES OUTPUT_NAME
    "${PLUGIN_OUTPUT_FILENAME}")
