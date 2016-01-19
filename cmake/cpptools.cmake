cmake_minimum_required(VERSION 2.8.11)

# don't work for 2.8.x
set(CMAKE_CXX_STANDARD 11)

set(AVX_ENABLED 1)
set(AVX2_ENABLED 1)

if (MSVC)
  # Turn on the ability to create folders to organize projects (.vcproj)
  # It creates "CMakePredefinedTargets" folder by default and adds CMake
  # defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    if (AVX2_ENABLED)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
    elseif (AVX_ENABLED)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX")
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 4) 
        # win32
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
    endif ()

  # fast, but maybe not for production
  # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ob2 /Oi /Os /Oy /GS- /fp:fast")  

elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -O3 -Wall -DNDEBUG")
    set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -mavx2 -mfma -fabi-version=0")
    #set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -ffast-math")
    #set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -fno-exceptions")
    #set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -pg")


elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    
    set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -O3 -Wall -DNDEBUG")
    set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -mfma -mavx2")
    #set(CMAKE_CXX_FLAGS                  "${CMAKE_CXX_FLAGS} -fno-exceptions")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
        
    # Clang hangs with Vector Class and AVX2    
    set(AVX_ENABLED 0)
    set(AVX2_ENABLED 0)
else ()
    message(FATAL_ERROR "Unknown C++ compiler.")
endif ()
