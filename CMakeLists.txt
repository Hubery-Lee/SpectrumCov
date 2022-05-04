cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(SpectrumCov)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})  #设置程序安装目录
add_subdirectory(src)

file(GLOB datas  ${PROJECT_SOURCE_DIR}/data/* )
install(FILES ${datas} DESTINATION bin)