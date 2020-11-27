aux_source_directory(. SRC_LIST)
aux_source_directory(./base SRC_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/base)

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux")
    include_directories(${PROJECT_SOURCE_DIR}/include/unix)
    aux_source_directory(./unix SRC_LIST)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

add_library(utils_static STATIC ${SRC_LIST})
add_library(utils_shared SHARED ${SRC_LIST})

set_target_properties(utils_static PROPERTIES OUTPUT_NAME "utils" )
set_target_properties(utils_shared PROPERTIES OUTPUT_NAME "utils" VERSION 1.2 SOVERSION 1)

INSTALL(
    TARGETS  utils_shared utils_static
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)

INSTALL(FILES 
    ${PROJECT_SOURCE_DIR}/include/kfifobuffer.h
    ${PROJECT_SOURCE_DIR}/include/log.h 
    ${PROJECT_SOURCE_DIR}/include/cpu.h 
    ${PROJECT_SOURCE_DIR}/include/singleton.h
    ${PROJECT_SOURCE_DIR}/include/guard.h
    ${PROJECT_SOURCE_DIR}/include/mutex.h
    ${PROJECT_SOURCE_DIR}/include/shell.h
    ${PROJECT_SOURCE_DIR}/include/stringutils.h
    ${PROJECT_SOURCE_DIR}/include/uuid.h
    ${PROJECT_SOURCE_DIR}/include/thread.h
    ${PROJECT_SOURCE_DIR}/include/runnable.h
    DESTINATION include
)