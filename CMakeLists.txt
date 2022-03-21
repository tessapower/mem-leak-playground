cmake_minimum_required(VERSION 3.16)
project(scratch_project VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()

add_subdirectory(app)
add_subdirectory(src)
