project (PANEL)


set (TARGET "switcher")
set (SOURCES switcher.cpp utils.cpp)
#set (HEADERS )
#set (DIST_SOURCES ${SOURCES} ${HEADERS} CMakeLists.txt)

set (LIB_DIR "/usr/X11/lib")
set (INCLUDE_DIR "/usr/X11/include")

INCLUDE_DIRECTORIES(${INCLUDE_DIR})

LINK_DIRECTORIES(${LIB_DIR})
#LINK_DIRECTORIES(${VTE_LIB_DIR})



add_executable (${TARGET} ${SOURCES})


target_link_libraries (${TARGET} X11 Xpm)

