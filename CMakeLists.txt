# cmake最低版本
cmake_minimum_required(VERSION 3.21)

option(USE_STD_SOURCE_LOCATION "" ON)
option(USE_CLASSIC_CONSOLE_API "" ON)
option(USE_ZLOG_MODULE "" ON)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(common)

# 包括模板
include(CMakePrintHelpers)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 項目名
project(zlog)

# set(target zlog)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/std:c17;/experimental:module;>")

# add_library(${target} INTERFACE)

# find_package(source_location REQUIRED)
# cmake_print_variables(source_location_FOUND)
# cmake_print_variables(source_location_INCLUDE_DIR)

## 庫開始
set(target zlog)

add_library(${target} INTERFACE)

include(GNUInstallDirs)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/lite" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

target_include_directories(${target}
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(${target}
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lite/source_location.cppm>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/lite/source_location.cppm>"
)

target_compile_definitions(${target}
  INTERFACE
    USE_SOURCE_LOCATION_MODULE=$<BOOL:${USE_SOURCE_LOCATION_MODULE}>)

target_install(${target} "0.0.1")

set(main main)
add_executable(${main})
target_sources(${main}
  PRIVATE
    src/main.cpp
    src/main.cppm
    include/zlog/source_location.hpp
    include/zlog/source_location.cppm
    include/zlog.hpp
    include/zlog/marco.h
    include/zlog/module.h
    include/zlog/stream.hpp
    include/zlog/color.cppm
    include/zlog/type.hpp
    include/zlog/common.h
    $<$<BOOL:${USE_ZLOG_MODULE}>:include/zlog.cppm>
)
# target_link_libraries(${main} PUBLIC ${zlog} source_location::source_location)
target_link_libraries(${main} PUBLIC ${zlog})
target_include_directories(${main} PRIVATE include)
target_compile_features(${main} PRIVATE cxx_std_20)
# 設置宏
target_compile_definitions(${main} PRIVATE
  USE_STD_SOURCE_LOCATION=$<BOOL:${USE_STD_SOURCE_LOCATION}>
  USE_ZLOG_MODULE=$<BOOL:${USE_ZLOG_MODULE}>
  USE_CLASSIC_CONSOLE_API=$<BOOL:${USE_CLASSIC_CONSOLE_API}>)
