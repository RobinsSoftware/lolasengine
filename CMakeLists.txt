# CactusEngine
cmake_minimum_required( VERSION 3.22 )
project( CactusEngine VERSION 0.1.0 )

# Config
set( FILE_OUTPUT_NAME CactusEngine ) # Output file name
set( FILE_OUTPUT_TYPE WIN32 ) # Output file type (WIN32/MACOSX_BUNDLE/EXCLUDE_FROM_ALL)

# GLFW (src jullietef/GLFW-CMake-starter)
find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory( dependencies/glfw )

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set( GAME_SRC src/engine.c )
     
add_executable( ${FILE_OUTPUT_NAME} ${FILE_OUTPUT_TYPE} ${GAME_SRC} )
target_link_libraries( ${FILE_OUTPUT_NAME} ${OPENGL_LIBRARIES} glfw )