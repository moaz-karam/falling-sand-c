cmake_minimum_required(VERSION 3.25)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MulitThreaded<$<CONFIG: Debug>: Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MulitThreaded<$<CONFIG: Release>: Release>")

project(falling-sand)

find_package(SDL3 CONFIG REQUIRED)

# target_compile_options(-lm)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE DATA_STRUCTURES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/data_structures/*.c")

add_executable(falling-sand "${MY_SOURCES}" "${DATA_STRUCTURES}")
target_include_directories(falling-sand PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(falling-sand SDL3::SDL3 m)