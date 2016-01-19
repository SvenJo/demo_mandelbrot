cmake_minimum_required(VERSION 2.8.11)

set(TARGET unit_tests)

include_directories(${CMAKE_SOURCE_DIR}/extern/catch)

set (HEADER_FILES
   stdafx.h
   test_helper.h
)

set (SOURCE_FILES
   mandel_tests.cpp
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

target_link_libraries(${TARGET} ${LIBS})

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/extern/${TBB_VERSION}/bin/${TBB_PLATFORM}/vc12/tbb_debug.dll"
        $<TARGET_FILE_DIR:${TARGET}>)

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/extern/${TBB_VERSION}/bin/${TBB_PLATFORM}/vc12/tbb.dll"
        $<TARGET_FILE_DIR:${TARGET}>)


