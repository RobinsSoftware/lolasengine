# config
set(CE_NAME testgame.exe) # project name
set(CE_VERSION 0.1.0) # project version
set(CE_OUTPUT_NAME cactusengine.exe) # file output name
set(CE_OUTPUT_TYPE WIN32) # file output type (WIN32/MACOSX_BUNDLE/EXCLUDE_FROM_ALL)
set(CE_MAIN_FILE ${CMAKE_SOURCE_DIR}/src/game.c)

# internal build script
cmake_minimum_required(VERSION 3.22)

project (cactusengine VERSION 0.1.0)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# dependencies
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw3)

# engine
add_subdirectory(${CMAKE_SOURCE_DIR}/src/engine)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

add_executable(${CE_OUTPUT_NAME} ${CE_OUTPUT_TYPE} ${CE_MAIN_FILE} ${CMAKE_SOURCE_DIR}/src/engine/window.c)
target_link_libraries(${CE_OUTPUT_NAME} ${OPENGL_LIBRARIES} glfw )