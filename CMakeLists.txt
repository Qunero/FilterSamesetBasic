cmake_minimum_required(VERSION 2.6)
PROJECT (FilterSameset)
ADD_SUBDIRECTORY(src)

# 下面的是路径测试
MESSAGE(STATUS "The BINARY dir is: " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "The SOURCE dir is: " ${PROJECT_SOURCE_DIR})

