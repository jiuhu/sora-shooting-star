cmake_minimum_required(VERSION 3.17)
project(sss)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(WpAddExecutable)
include(WpAddLibrary)
include(WpCheckCompiler)

wp_check_compiler()

message("Platform:" ${WP_PLATFORM})

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(BIN_DIR ${BUILD_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib/${WP_PLATFORM})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib/${WP_PLATFORM})

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)
set(SCRIPTS_DIR ${CMAKE_SOURCE_DIR}/scripts)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

add_subdirectory(external)
add_subdirectory(src)
