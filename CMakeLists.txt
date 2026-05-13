cmake_minimum_required(
  VERSION 3.28) # Kittens will die if you switch to an earlier version of CMake.

project(thin-bridge)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-MMD -MP)

FILE(GLOB SOURCES_MAIN
    CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "src/main.c")

FILE(GLOB_RECURSE SOURCES_LIB
    CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "src/lib/*.c") # added for clang-tidy 

FILE(GLOB_RECURSE INCLUDES_LIB
    CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "include/*.h") # added for clang-tidy 

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_MAIN})

if(NOT "${SOURCES_LIB}" STREQUAL "")
  add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES_LIB})
  target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC include)

  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)
endif()

# SOURCES
#   _MAIN           - contains main.cpp
#   _LIB            - contains all library code for the main app
