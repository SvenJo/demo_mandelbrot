cmake_minimum_required(VERSION 2.8.11)

project(MandelBrot)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cpptools)
include(openMPTools)
include(FindTBB)

if (MSVC)
  # single bineary folder
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endif()

file (GLOB MANDEL_HEADERS
  "include/mandel/*.h"
)

file (GLOB EASY_HEADERS
  "include/easy/*.h"
)

file (GLOB EASY_MFC_HEADERS
  "include/easy/mfc/*.h"
)

file (GLOB EASY_QT_HEADERS
  "include/easy/qt/*.h"
)

file (GLOB GLOBAL_HEADERS 
  "include/*.h"
  "${PROJECT_BINARY_DIR}/config.h"
)

include_directories(${CMAKE_SOURCE_DIR}/include/)

######################
# Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

#find_package(Boost 1.59.0 COMPONENTS program_options)
find_package(Boost 1.60.0 COMPONENTS program_options)

# includes from the extern folders (3rd party libs)

if(Boost_FOUND)
  set(BOOST_FOUND 1)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif()

# copy c++ vector class from agner for to /extern/vectorclass
if(EXISTS "${CMAKE_SOURCE_DIR}/extern/vectorclass/vectorclass.h")
    include_directories(${CMAKE_SOURCE_DIR}/extern/vectorclass)
    set(VECTORCLASS_FOUND 1)
endif()    

configure_file(cmake/config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
# copy the source and libs to extern/bench
#  add_subdirectory (bench)
endif()

add_subdirectory (demo)

# copy catch.hpp to extern/catch
if(EXISTS "${CMAKE_SOURCE_DIR}/extern/catch/catch.hpp")
    add_subdirectory (tests)
endif()

if(Boost_FOUND)
# todo: add the sources for the ui demo
#  add_subdirectory (mandel_ui)
endif()
