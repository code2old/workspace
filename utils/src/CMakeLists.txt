aux_source_directory(. SRC_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include) 

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")
 
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    include_directories(${PROJECT_SOURCE_DIR}/include/unix)
    aux_source_directory(./unix SRC_LIST)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    include_directories(${PROJECT_SOURCE_DIR}/include/win32) 
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
 
MESSAGE(STSTUS "###################################")

add_library(utils_static STATIC ${SRC_LIST})
add_library(utils_shared SHARED ${SRC_LIST})

target_link_libraries (utils_static pthread)
target_link_libraries (utils_shared pthread)

set_target_properties(utils_static PROPERTIES OUTPUT_NAME "utils" )
set_target_properties(utils_shared PROPERTIES OUTPUT_NAME "utils" VERSION 1.2 SOVERSION 1)

INSTALL(
    TARGETS  utils_shared utils_static
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)

INSTALL(FILES 
    ${PROJECT_SOURCE_DIR}/include/log.h
    ${PROJECT_SOURCE_DIR}/include/mutex.h
    ${PROJECT_SOURCE_DIR}/include/guard.h
    DESTINATION include
)