PROJECT (FilterSamesetBasic)
FIND_PACKAGE(Qt4 REQUIRED)
ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE(${QT_USE_FILE})

SET(FilterSamesetBasic_SOURCES main.cpp mainwidget.cpp)
SET(FilterSamesetBasic_HEADERS mainwidget.h)
SET(FilterSamesetBasic_FORMS ../ui/mainwidget.ui)

QT4_WRAP_CPP(FilterSamesetBasic_HEADERS_MOC ${FilterSamesetBasic_HEADERS})
QT4_WRAP_UI(FilterSamesetBasic_FORMS_HEADERS ${FilterSamesetBasic_FORMS})

# 添加共享库路
IF(LINUX)
    MESSAGE(STATUS "Found LINUX")
    TARGET_LINK_LIBRARIES(FilterSamesetBasic ${QT_LIBRARIES})
ELSEIF(APPLE)
    MESSAGE(STATUS "Found APPLE")
    TARGET_LINK_LIBRARIES(FilterSamesetBasic
    /Volumes/Design/LocalSoft/Qt/Desktop/Qt/4.8.1/gcc/lib/QtGui.la 
    /Volumes/Design/LocalSoft/Qt/Desktop/Qt/4.8.1/gcc/lib/QtCore.la )
ENDIF()
#LINK_DIRECTORIES(${QT_LIBRARIES})

# 添加编译路径到包含的路径中，否则部分编译出的头文件找不到
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(FilterSamesetBasic ${FilterSamesetBasic_SOURCES}
    ${FilterSamesetBasic_FORMS_HEADERS}
    ${FilterSamesetBasic_HEADERS_MOC}
)


