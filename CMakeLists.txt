# +------------------------------------------------------------+
# |  * user config                                             |
# +------------------------------------------------------------+

# config
set(LE_NAME testgame) # project name
set(LE_VERSION 0.1.0) # project version
set(LE_OUTPUT_NAME testgame.exe) # file output name
set(LE_OUTPUT_TYPE WIN32) # file output type (WIN32/MACOSX_BUNDLE/EXCLUDE_FROM_ALL)

# +------------------------------------------------------------+
# |  * internal build script                                   |
# +------------------------------------------------------------+

cmake_minimum_required(VERSION 3.22)

project(${LE_NAME} VERSION 0.1.0)

# glfw
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw3)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

# engine sources
add_subdirectory(src)
add_subdirectory(engine)

include_directories(engine/include)

add_executable(${LE_OUTPUT_NAME} ${LE_OUTPUT_TYPE} ${GAME_SOURCES} ${ENGINE_SOURCES})
target_link_libraries(${LE_OUTPUT_NAME} ${OPENGL_LIBRARIES} glfw )