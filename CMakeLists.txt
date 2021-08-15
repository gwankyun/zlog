# cmake最低版本
cmake_minimum_required(VERSION 3.21)

option(USE_STD_SOURCE_LOCATION "" ON)

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

# target_include_directories(${target}
#   INTERFACE
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# )

# # install the target and create export-set
# install(TARGETS ${target}
#   EXPORT ${target}Targets
#   LIBRARY DESTINATION lib
#   ARCHIVE DESTINATION lib
#   RUNTIME DESTINATION bin
#   INCLUDES DESTINATION include
# )

# # install header file
# install(DIRECTORY include/ztest DESTINATION include)

# # generate and install export file
# install(EXPORT ${target}Targets
#   FILE ${target}Targets.cmake
#   NAMESPACE ${target}::
#   DESTINATION lib/cmake/${target}
# )

# # include CMakePackageConfigHelpers macro
# include(CMakePackageConfigHelpers)

# # set version
# set(version 0.0.1)

# set_property(TARGET ${target} PROPERTY VERSION ${version})
# set_property(TARGET ${target} PROPERTY SOVERSION 0)
# set_property(TARGET ${target} PROPERTY
#   INTERFACE_${target}_MAJOR_VERSION 0)
# set_property(TARGET ${target} APPEND PROPERTY
#   COMPATIBLE_INTERFACE_STRING ${target}_MAJOR_VERSION
# )

# # generate the version file for the config file
# write_basic_package_version_file(
#   "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
#   VERSION "${version}"
#   COMPATIBILITY AnyNewerVersion
# )

# # create config file
# configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}Config.cmake.in
#   "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
#   INSTALL_DESTINATION lib/cmake/${target}
# )

# # install config files
# install(FILES
#   "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
#   "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
#   DESTINATION lib/cmake/${target}
# )

# # generate the export targets for the build tree
# export(EXPORT ${target}Targets
#   FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${target}Targets.cmake"
#   NAMESPACE ${target}::
# )
## 庫結束

# add_subdirectory(source_location)
# add_library(source_location::source_location ALIAS source_location)

set(main main)
add_executable(${main})
target_sources(${main}
  PRIVATE
    src/main.cpp
    include/source_location.hpp
    include/zlog.hpp
    include/zlog.cppm
    include/zlog/marco.h
)
# target_link_libraries(${main} PUBLIC ${zlog} source_location::source_location)
target_link_libraries(${main} PUBLIC ${zlog})
target_include_directories(${main} PRIVATE include)
target_compile_features(${main} PRIVATE cxx_std_20)
# 設置宏
target_compile_definitions(${main} PRIVATE USE_STD_SOURCE_LOCATION=$<BOOL:${USE_STD_SOURCE_LOCATION}>)
