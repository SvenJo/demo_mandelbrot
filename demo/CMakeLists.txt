cmake_minimum_required(VERSION 2.8.11)

set(TARGET demo)

set (HEADER_FILES
   stdafx.h
   doloopdemo.h
   floatinitdemo.h
   paralleldemo.h
   perfdemo.h
   printiterations.h
   simddemo.h
   simpleexample.h
   stepdemo.h
   transformdemo.h
   openmpscheduledemo.h
   unrolldemo.h
   warmupdemo.h
   recursion.h
   test.h
)

set (SOURCE_FILES
   demo.cpp
   stdafx.cpp
)

if(TBB_FOUND)
   include_directories(${TBB_INCLUDE_DIR})
   link_directories(${TBB_LIBRARY_DIR})
endif()

source_group("mandel" FILES ${MANDEL_HEADERS})
source_group("global" FILES ${GLOBAL_HEADERS})

add_executable(${TARGET}
   ${SOURCE_FILES}
   ${HEADER_FILES}
   ${MANDEL_HEADERS}
   ${GLOBAL_HEADERS}
)

if(TBB_FOUND)
    target_link_libraries(${TARGET} ${TBB_LIBRARIES})
endif()

if (MSVC)
   set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "/Yustdafx.h")
   set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")
endif()

#target_link_libraries(demoexe ${LIBS})
target_link_libraries(${TARGET} ${LIBS} ${Boost_LIBRARIES})

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/extern/${TBB_VERSION}/bin/${TBB_PLATFORM}/vc12/tbb_debug.dll"
        $<TARGET_FILE_DIR:${TARGET}>)

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/extern/${TBB_VERSION}/bin/${TBB_PLATFORM}/vc12/tbb.dll"
        $<TARGET_FILE_DIR:${TARGET}>)

