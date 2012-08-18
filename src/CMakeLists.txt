FIND_PACKAGE(Qt4 REQUIRED)
ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE(${QT_USE_FILE})

# 下面的是路径测试
#MESSAGE(STATUS "The BINARY dir is: " ${PROJECT_BINARY_DIR})
#MESSAGE(STATUS "The SOURCE dir is: " ${PROJECT_SOURCE_DIR})

# 设置输出程序的路径，为编译目录下的bin目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

SET(FilterSamesetBasic_SOURCES main.cpp mainwidget.cpp)
SET(FilterSamesetBasic_HEADERS mainwidget.h)
SET(FilterSamesetBasic_FORMS ../ui/mainwidget.ui)

QT4_WRAP_CPP(FilterSamesetBasic_HEADERS_MOC ${FilterSamesetBasic_HEADERS})
QT4_WRAP_UI(FilterSamesetBasic_FORMS_HEADERS ${FilterSamesetBasic_FORMS})

# 添加编译路径到包含的路径中，否则部分编译出的头文件找不到
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(FilterSamesetBasic ${FilterSamesetBasic_SOURCES}
	${FilterSamesetBasic_FORMS_HEADERS}
	${FilterSamesetBasic_HEADERS_MOC}
	)

# 添加共享库路，注意该配置必须添加在设置应用程序后，即ADD_EXECUTABLE后面
IF(WIN32)
	MESSAGE(STATUS "Found WIN32 OS")
	#TARGET_LINK_LIBRARIES(FilterSamesetBasic ${QT_LIBRARIES})
ELSEIF(APPLE)
	MESSAGE(STATUS "Found APPLE OS")    
	#TARGET_LINK_LIBRARIES(FilterSamesetBasic ${QT_LIBRARIES})
ELSEIF(UNIX)
	MESSAGE(STATUS "Found UNIX or UNIX-like OS")    
ENDIF()

# updated: 将链接方式放到系统检查外面；
TARGET_LINK_LIBRARIES(FilterSamesetBasic ${QT_LIBRARIES})

#LINK_DIRECTORIES(${QT_LIBRARIES})

