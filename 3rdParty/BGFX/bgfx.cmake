cmake_minimum_required(VERSION "3.0")
project(bgfx)

add_definitions(-D__STDC_FORMAT_MACROS)

set(includes "bx/include" "bimg/include" "bgfx/include" "bgfx/3rdparty" "bgfx/3rdparty/dxsdk/include" "bgfx/3rdparty/khronos")

file(GLOB sources "bgfx/include/bgfx/**.h" "bgfx/src/*.cpp" "bgfx/src/*.h")
get_filename_component(full_path_sources "bgfx/src" ABSOLUTE)
list(REMOVE_ITEM sources "${full_path_sources}/amalgamated.cpp")

if(MSVC)
	list(REMOVE_ITEM sources "${full_path_sources}/glcontext_glx.cpp" "${full_path_sources}/glcontext_egl.cpp")
elseif(APPLE AND NOT UNIX)
	list(APPEND sources "bgfx/src/*.mm")
endif()

add_library(bgfx ${sources})

set_property(TARGET bgfx PROPERTY CXX_STANDARD 14)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
	add_definitions(-DBGFX_CONFIG_DEBUG=1)
endif()

target_include_directories(bgfx PRIVATE ${includes})

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	target_include_directories(bgfx PRIVATE "bx/include/compat/msvc")
elseif(WIN32)
	target_include_directories(bgfx PRIVATE "bx/include/compat/mingw")
elseif(APPLE AND NOT UNIX)
	target_include_directories(bgfx PRIVATE "bx/include/compat/osx")
endif()