#header
cmake_minimum_required(VERSION 3.8)
#set vars
set(TARGET_NAME project_two)
project(${TARGET_NAME} VERSION 0.0.1 DESCRIPTION "Project Description")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HEADER_FILES modules/AppInit.h modules/worldgen/tile.h modules/worldgen/terrain_type.h modules/worldgen/chunk.h modules/worldgen/object_type.h modules/worldgen/map.h modules/ui/game_ui.h modules/ui/button.h modules/content/content_manager.h modules/ui/button_type.h)
set(SOURCE_FILES main.cpp modules/AppInit.cpp modules/worldgen/tile.cpp modules/worldgen/map.cpp modules/ui/game_ui.cpp modules/worldgen/chunk.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lsqlite3")
#add exec
add_executable(project_two ${HEADER_FILES} ${SOURCE_FILES})
#find pkgs
find_package(raylib 3.0 REQUIRED)
#TARGET Link
target_link_libraries(${PROJECT_NAME} raylib)
#target init
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_OUTPUT_NAME "${TARGET_NAME}d" RELEASE_OUTPUT_NAME ${TARGET_NAME})
target_compile_options(${TARGET_NAME} PUBLIC -Wall -Wextra -pedantic -fpermissive)

